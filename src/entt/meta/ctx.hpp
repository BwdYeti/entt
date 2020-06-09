#ifndef ENTT_META_CTX_HPP
#define ENTT_META_CTX_HPP


#include "../core/attribute.h"
#include "../config/config.h"
#include "internal.hpp"


namespace entt {


/**
 * @cond TURN_OFF_DOXYGEN
 * Internal details not to be documented.
 */


namespace internal {


struct ENTT_API meta_context {
    // we could use the lines below but VS2017 returns with an ICE if combined with ENTT_API despite the code being valid C++
    //     inline static meta_type_node *local = nullptr;
    //     inline static meta_type_node **global = &local;

    [[nodiscard]] static meta_type_node * & local() ENTT_NOEXCEPT {
        static meta_type_node *chain = nullptr;
        return chain;
    }

    [[nodiscard]] static meta_type_node ** & global() ENTT_NOEXCEPT {
        static meta_type_node **chain = &local();
        return chain;
    }

    static void detach(const meta_type_node *node) ENTT_NOEXCEPT {
        auto **it = global();

        while(*it && *it != node) {
            it = &(*it)->next;
        }

        if(*it) {
            *it = (*it)->next;
        }
    }
};


}


/**
 * Internal details not to be documented.
 * @endcond TURN_OFF_DOXYGEN
 */


/*! @brief Opaque container for a meta context. */
struct meta_ctx {
    /**
     * @brief Binds the meta system to a given context.
     * @param other A valid context to which to bind.
     */
    static void bind(meta_ctx other) ENTT_NOEXCEPT {
        internal::meta_context::global() = other.ctx;
    }

private:
    internal::meta_type_node **ctx{&internal::meta_context::local()};
};


}


#endif
