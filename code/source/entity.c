// file: source/entity.c

#ifdef LIBRG_EDITOR
#include <librg.h>
#include <zpl.h>
#endif

LIBRG_BEGIN_C_DECLS

// =======================================================================//
// !
// ! Basic entity manipulation
// !
// =======================================================================//

int8_t librg_entity_track(librg_ctx *ctx, int64_t entity_id) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    if (librg_entity_tracked(ctx, entity_id) == LIBRG_TRUE)
        return LIBRG_ENTITY_ALREADY_TRACKED;

    librg_entity_t entity = {0};
    librg_table_entity_set(&ictx->entity_map, entity_id, entity);

    /* set defaults */
    librg_entity_chunk_set(ctx, entity_id, LIBRG_CHUNK_INVALID);
    librg_entity_owner_set(ctx, entity_id, LIBRG_OWNER_INVALID, 0);

    return LIBRG_OK;
}

int8_t librg_entity_untrack(librg_ctx *ctx, int64_t entity_id) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    if (librg_entity_tracked(ctx, entity_id) == LIBRG_FALSE)
        return LIBRG_ENTITY_UNTRACKED;

    librg_table_entity_remove(&ictx->entity_map, entity_id);

    return LIBRG_OK;
}

int8_t librg_entity_tracked(librg_ctx *ctx, int64_t entity_id) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    librg_entity_t *entity = librg_table_entity_get(&ictx->entity_map, entity_id);
    return entity == NULL ? LIBRG_FALSE : LIBRG_TRUE;
}

int8_t librg_entity_userdata_set(librg_ctx *ctx, int64_t entity_id, void *data) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    librg_entity_t *entity = librg_table_entity_get(&ictx->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    entity->userdata = data;
    return LIBRG_OK;
}

void *librg_entity_userdata_get(librg_ctx *ctx, int64_t entity_id) {
    LIBRG_ASSERT(ctx); if (!ctx) return NULL;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    librg_entity_t *entity = librg_table_entity_get(&ictx->entity_map, entity_id);
    if (entity == NULL) return NULL;

    return entity->userdata;
}

// =======================================================================//
// !
// ! Main entity data methods
// !
// =======================================================================//

int8_t librg_entity_type_set(librg_ctx *ctx, int64_t entity_id, uint8_t type) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    librg_entity_t *entity = librg_table_entity_get(&ictx->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    entity->type = type;
    return LIBRG_OK;
}

int16_t librg_entity_type_get(librg_ctx *ctx, int64_t entity_id) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    librg_entity_t *entity = librg_table_entity_get(&ictx->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    return entity->type;
}

int8_t librg_entity_chunk_set(librg_ctx *ctx, int64_t entity_id, librg_chunk chunk) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    librg_entity_t *entity = librg_table_entity_get(&ictx->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    for (int i = 0; i < LIBRG_ENTITY_MAXCHUNKS; ++i) entity->chunks[i] = LIBRG_CHUNK_INVALID;
    entity->chunks[0] = chunk;

    return LIBRG_OK;
}

librg_chunk librg_entity_chunk_get(librg_ctx *ctx, int64_t entity_id) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    librg_entity_t *entity = librg_table_entity_get(&ictx->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    return entity->chunks[0];
}

int8_t librg_entity_owner_set(librg_ctx *ctx, int64_t entity_id, int64_t owner_id, int8_t observed_chunk_radius) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    librg_entity_t *entity = librg_table_entity_get(&ictx->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    entity->owner_id = owner_id;
    entity->observed_radius = observed_chunk_radius;

    return LIBRG_OK;
}

int64_t librg_entity_owner_get(librg_ctx *ctx, int64_t entity_id) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    librg_entity_t *entity = librg_table_entity_get(&ictx->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    return entity->owner_id;
}

int8_t librg_entity_dimension_set(librg_ctx *ctx, int64_t entity_id, int32_t dimension) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    librg_entity_t *entity = librg_table_entity_get(&ictx->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    entity->dimension = dimension;
    return LIBRG_OK;
}

int32_t librg_entity_dimension_get(librg_ctx *ctx, int64_t entity_id) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    librg_entity_t *entity = librg_table_entity_get(&ictx->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    return entity->dimension;
}

// =======================================================================//
// !
// ! Advanced entity data methods
// !
// =======================================================================//

int8_t librg_entity_chunkarray_set(librg_ctx *ctx, int64_t entity_id, librg_chunk *values, size_t chunk_amount) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    librg_entity_t *entity = librg_table_entity_get(&ictx->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    LIBRG_ASSERT(chunk_amount > 0 && chunk_amount < LIBRG_ENTITY_MAXCHUNKS);

    for (int i = 0; i < LIBRG_ENTITY_MAXCHUNKS; ++i) entity->chunks[i] = LIBRG_CHUNK_INVALID;
    zpl_memcopy(entity->chunks, values, sizeof(librg_chunk) * zpl_min(chunk_amount, LIBRG_ENTITY_MAXCHUNKS));

    return LIBRG_OK;

}

size_t librg_entity_chunkarray_get(librg_ctx *ctx, int64_t entity_id, librg_chunk *results, size_t buffer_limit) {
    LIBRG_ASSERT(ctx); if (!ctx) return LIBRG_CONTEXT_INVALID;
    librg_ctx_t *ictx = (librg_ctx_t *)ctx;

    librg_entity_t *entity = librg_table_entity_get(&ictx->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    LIBRG_ASSERT(results);
    size_t count = 0;

    for (size_t i = 0; i < zpl_min(buffer_limit, LIBRG_ENTITY_MAXCHUNKS); ++i) {
        if (entity->chunks[i] != LIBRG_CHUNK_INVALID) {
            results[count++] = entity->chunks[i];
        }
    }

    return count;
}

#if 0
int librg_entity_refresh_set(librg_ctx *, int64_t entity_id, int type, float value); // ? {
    return LIBRG_OK
}

int librg_entity_refresh_get(librg_ctx *, int64_t entity_id, int *type, float *value) {
    return LIBRG_OK
}
// TODO: entity visibility

#endif

LIBRG_END_C_DECLS