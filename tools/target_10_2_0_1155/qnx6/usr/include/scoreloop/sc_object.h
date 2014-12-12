/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_object.h
 * @brief       ScoreloopCore - object debug facilities.
 *
 * @addtogroup  SC_Object
 * @{
 *
 * ScoreloopCore - object debug facilities.
 */

#ifndef __SC_OBJECT_H__
#define __SC_OBJECT_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_platform.h>
#include <scoreloop/sc_types.h>

#ifdef __cplusplus
extern "C" {
#endif
    
/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** 
 * Opaque SC_Object handle. You can cast any other handle to this base handle for introspection purposes.
 *
 * @since 10.0.0
 */
typedef struct SC_Object_tag* SC_Object_h;

/**
 * @brief Callback type for object iteration.
 *
 * Pass a method of this type to the SC_Object_IterateAllocatedObjects method. The method will then
 * be called for each allocated object by passing the object as an argument to the method.
 *
 * @since 10.0.0
 */
typedef void (*SC_ObjectIteratorCallback_t)(SC_Object_h object);

/**
 * @brief Pointer type to the type information structure
 *
 * @since 10.0.0
 */
typedef const struct _SCTypeInfo_tag* SC_TypeInfo_p;

/*-------------------------------------------------------------------------------------*
 * Macros
 *-------------------------------------------------------------------------------------*/

/**
 * Returns SC_TRUE if object is of a given type.
 *
 * Note: this doesn't take inheritance into account.
 *
 * @since 10.0.0
 */
#define SC_IS_OF_TYPE(obj, type) \
    SC_Object_IsOfType((SC_Object_h) obj, _##type##_TypeInfoPtr)

/**
 * Returns SC_TRUE if object is an instance of a given type.
 *
 * Note: this macro takes inheritance into account.
 *
 * @since 10.0.0
 */
#define SC_INSTANCE_OF(obj, type) \
    SC_Object_InstanceOf((SC_Object_h) obj, _##type##_TypeInfoPtr)

/**
 * Performs casting to a given type
 *
 * Note: returns NULL if object is not instance of a given type.
 *
 * @since 10.0.0
 */
#define SC_DYNAMIC_CAST(obj, type) \
    ((type##_h) SC_Object_DynamicCast((SC_Object_h) obj, _##type##_TypeInfoPtr))

/** Macro for defining type descriptors for any SC_xxx type. 
 *
 * @since 10.0.0
 */
#define SC_TYPEINFO(klass) \
    SC_PUBLISHED extern const SC_TypeInfo_p _##klass##_TypeInfoPtr; \
    SC_TypeInfo_p _##klass##_GetParentType()

/** Define type info pointer for SC_Object 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_Object);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

#if SC_TRACK_ALLOCS

/**
 * Start recording object allocations
 *
 * @since 10.0.0
 */ 
SC_PUBLISHED void SC_Object_StartTrackingAllocs();

/**
 * Stop recording object allocations
 *
 * @since 10.0.0
 */ 
SC_PUBLISHED void SC_Object_StopTrackingAllocs();

/**
 * Clear the list of allocated objects
 *
 * @since 10.0.0
 */ 
SC_PUBLISHED void SC_Object_FlushObjectLists();

/**
 * Iterate all objects still allocated since recording started
 *
 * @param iteratorCallback the method to invoke for each object
 *
 * @return unsigned int returns the total number of allocated objects since recording started
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_Object_IterateAllocatedObjects(SC_ObjectIteratorCallback_t iteratorCallback);

#endif


/**
 * @brief Increments object's reference counter.
 *
 * This methid increments object's reference counter.
 *
 * @param self          the object handle
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Object_Retain(SC_Object_h self);

/**
 * @brief Decrements object's reference counter, destroys object when counter reaches 0
 *
 * This method decrements object's reference counter, destroys object when counter reaches 0
 *
 * @param self          the object handle
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Object_Release(SC_Object_h self);

/**
 * @brief Copy a human readable description of an object.
 *
 * Copy a human readable description of an object.
 *
 * @param self          the object to describe.
 * @param buffer        a buffer to hold the description.
 * @param bufferSize    the size of the buffer
 * @return unsigned int if returned unsigned int >= bufferSize, truncation occurred.
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_Object_Describe(SC_Object_h self, char *buffer, unsigned int bufferSize);

/**
 * @brief Get the current retain count.
 *
 * This method gets the current retain count.
 *
 * @param self  the object to get the retain count for.
 * @return unsigned int the currrent retain count.
 *
 * @since 10.0.0
 */     
SC_PUBLISHED unsigned int SC_Object_GetRetainCount(SC_Object_h self);

/**
 * @brief Check if given object is of a given type.
 *
 * This method checks if given object is of a given type.
 *
 * Note: you should use SC_IS_OF_TYPE wrapper macro.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Object_IsOfType(const SC_Object_h self,
        const SC_TypeInfo_p type);

/**
 * @brief Check if given object implements a given type.
 *
 * This method checks if given object implements a given type.
 *
 * Note: you should use SC_INSTANCE_OF wrapper macro.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Object_InstanceOf(const SC_Object_h self,
        const struct _SCTypeInfo_tag* type);

/**
 * @brief Check if object can be cast to given type
 *
 * This method checks if object can be cast to given type
 *
 * Note: you should use SC_DYNAMIC_CAST wrapper macro.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void * SC_Object_DynamicCast(const SC_Object_h self,
        const struct _SCTypeInfo_tag* expectedType);

#ifdef __cplusplus
}
#endif

#endif /* __SC_OBJECT_H__ */

/*! @} */

