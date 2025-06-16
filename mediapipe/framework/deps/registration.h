//
// Created by MSD on 12/06/2025.
//

#ifndef MEDIAPIPE_DEPS_REGISTRATION_H_
#define MEDIAPIPE_DEPS_REGISTRATION_H_

#include <algorithm>
#include <functional>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "absl/base/macros.h"
#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/log/absl_check.h"
#include "absl/log/absl_log.h"
#include "absl/meta/type_traits.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "absl/synchronization/mutex.h"
#include "mediapipe/framework/deps/registration_token.h"
#include "mediapipe/framework/port/canonical_errors.h"
#include "mediapipe/framework/port/statusor.h"

namespace mediapipe {
    // Usage:
    //
    // === Defining a registry ================================================
    //
    //  class Widget {};
    //
    //  using WidgetRegistry =
    //      GlobalFactoryRegistry<unique_ptr<Widget>,                 // return
    //                            unique_ptr<Gadget>, const Thing*>   // args
    //
    // === Registering an implementation =======================================
    //
    //  class MyWidget : public Widget {
    //    static unique_ptr<Widget> Create(unique_ptr<Gadget> arg,
    //                                     const Thing* thing) {
    //      return MakeUnique<Widget>(std::move(arg), thing);
    //    }
    //    ...
    //  };
    //
    //  REGISTER_FACTORY_FUNCTION_QUALIFIED(
    //      WidgetRegistry, widget_registration,
    //      ::my_ns::MyWidget, MyWidget::Create);
    //
    // === Using std::function =================================================
    //
    //  class Client {};
    //
    //  using ClientRegistry =
    //      GlobalFactoryRegistry<absl::StatusOr<unique_ptr<Client>>;
    //
    //  class MyClient : public Client {
    //   public:
    //    MyClient(unique_ptr<Backend> backend)
    //      : backend_(std::move(backend)) {}
    //   private:
    //     const std::unique_ptr<Backend> backend_;
    //  };
    //
    //  // Any std::function that returns a Client is valid to pass here. Below,
    //  // we use a lambda.
    //  REGISTER_FACTORY_FUNCTION_QUALIFIED(
    //      ClientRegistry, client_registration,
    //      ::my_ns::MyClient,
    //      []() {
    //        auto backend = absl::make_unique<Backend>("/path/to/backend");
    //        const absl::Status status = backend->Init();
    //        if (!status.ok()) {
    //          return status;
    //        }
    //        std::unique_ptr<Client> client
    //            = absl::make_unique<MyClient>(std::move(backend));
    //        return client;
    //      });
    //
    // === Using the registry to create instances ==============================
    //
    //  // Registry will return absl::StatusOr<Object>
    //  absl::StatusOr<unique_ptr<Widget>> s_or_widget =
    //      WidgetRegistry::CreateByName(
    //          "my_ns.MyWidget", std::move(gadget), thing);
    //  // Registry will return NOT_FOUND if the name is unknown.
    //  if (!s_or_widget.ok()) ... // handle error
    //  DoStuffWithWidget(std::move(s_or_widget).value());
    //
    //  // It's also possible to find an instance by name within a source namespace.
    //  auto s_or_widget = WidgetRegistry::CreateByNameInNamespace(
    //      "my_ns.sub_namespace", "MyWidget");
    //
    //  // It's also possible to just check if a name is registered without creating
    //  // an instance.
    //  bool registered = WidgetRegistry::IsRegistered("my_ns::MyWidget");
    //
    //  // It's also possible to iterate through all registered function names.
    //  // This might be useful if clients outside of your codebase are registering
    //  // plugins.
    //  for (const auto& name : WidgetRegistry::GetRegisteredNames()) {
    //    absl::StatusOr<unique_ptr<Widget>> s_or_widget =
    //        WidgetRegistry::CreateByName(name, std::move(gadget), thing);
    //    ...
    //  }
    //
    // === Injecting instances for testing =====================================
    //
    // Unregister unregisterer(WidgetRegistry::Register(
    //     "MockWidget",
    //      [](unique_ptr<Gadget> arg, const Thing* thing) {
    //        ...
    //      }));

    namespace registration_internal {
        inline constexpr char kCxxSep[] = "::";
        inline constexpr char kNameSep[] = ".";
        template <typename T>
        struct WrapStatusOr {
            using type = absl::StatusOr<T>;
        };

        // Specialization to avoid double-wrapping types that are already StatusOrs.
        template <typename T>
        struct WrapStatusOr<absl::StatusOr<T>> {
            using type = absl::StatusOr<T>;
        };

        // Defining a member of this type causes P to be ODR-used, which forces its
        // instantiation if it's a static member of a template.
        // Previously we depended on the pointer's value to determine whether the size
        // of a character array is 0 or 1, forcing it to be instantiated so the
        // compiler can determine the object's layout. But using it as a template
        // argument is more compact.
        template <auto* p>
        struct ForceStaticInstantiation {
			#ifdef _MSC_VER
          		static constexpr bool Use() { return p != nullptr; }
                char force_static[Use()];
          	#endif
        };
    }

    class NamespaceAllowlist {
      public:
        static const absl::flat_hash_set<std::string>& TopNamespaces();
    };

    template <typename R, typename... Args>
    class FunctionRegistry {
      public:
        using Function = std::function<R(Args...)>;
        using ReturnType = typename registration_internal::WrapStatusOr<R>::type;

        FunctionRegistry() {}
        FunctionRegistry(const FunctionRegistry&) = delete;
        FunctionRegistry& operator=(const FunctionRegistry&) = delete;

        RegistrationToken Register(absl::string_view name, Function func) {
          ABSL_LOCKS_EXCLUDED(lock_);
          std::string normalized_name = GetNormalizedName(name);
          absl::WriterMutexLock lock(&lock_);
          std::string adjusted_name = GetAdjustedName(normalized_name);
          if (adjusted_name == normalized_name) {
            functions_.insert(std::make_pair(adjusted_name, func));
          }
          if(functions_.insert(std::make_pair(normalized_name, std::move(func))).second) {
            return RegistrationToken(
                [this, normalized_name]() {Unregister(normalized_name); });
          }
		  ABSL_LOG(FATAL) << "Function with name " << name << " already registered";
          return RegistrationToken([] () {});
        }

        private:
          mutable absl::Mutex lock_;
          absl::flat_hash_map<std::string, Function> functions_ ABSL_GUARDED_BY(lock_);

          // For names included in NamespaceAllowlist, strips the namespace.
          std::string GetAdjustName(absl::string_view name) {
            using ::mediapipe::registration_internal::kCxxSep;
            std::vector<std::string> names = absl::StrSplit(name, kCxxSep);
            std::string base_name = names.back();
            names.pop_back();
            std::string ns = absl::StrJoin(names, kCxxSep);
            if (NamespaceAllowlist::TopNamespaces().count(ns)) {
				return base_name;
            }
            return std::string(name);
          }

          void Unregister(absl::string_view name) {
            absl::WriterMutexLock lock(&lock_);
            std::string adjusted_name = GetAdjustName(name);
            if (adjusted_name != name) {
              functions_.erase(adjusted_name);
            }
            functions_.erase(name);
          }
    };
}

#endif //MEDIAPIPE_DEPS_REGISTRATION_H_
