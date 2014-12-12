/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef UNIFIED_DATASOURCE_C_H_
#define UNIFIED_DATASOURCE_C_H_

__BEGIN_DECLS

/*
* @details
* This api provides an interface for clients to plugin their data to HUB
* Steps to plugin to HUB
* 1. Clients would register into HUB with required Registraion data - name , assetpath
* @code
*   uds_context_t udsHandle;
*    int descriptor;
*    int retVal = -1;
*    int serviceId = 0;
*    int status = 0;
*    bool async = false;
*    bool ret = false;
*
*   if ((retVal = uds_init(&udsHandle, async)) == UDS_SUCCESS)
*   {
*     char* serviceURL = "c_lib_service";
*     char* libPath = "";
*     char* assetPath = "/apps/com.example.UDSTestApp.testDev__UDSTestApp9ded287c/app/public/assets/images";
*     if( (retVal = uds_register_client(udsHandle, serviceURL, libPath, assetPath)) != UDS_SUCCESS)
*     {
*          printf("uds_register_client call failed with error %d\n", retVal);
*
*     }
*     if (retVal == UDS_SUCCESS)
*     {
*         serviceId = uds_get_service_id(udsHandle);
*         status = uds_get_service_status(udsHandle);
*     }
*  }
*  printf("uds_register_client call successful with %d as serviceId and %d as status\n", serviceId, status);
*@endcode
*
* 2.Client would then add accounts associated with its service ,
*   This would result in creation of a Tab in the main Hub view to view
*   the registered clients data
* @code
*  uds_account_data_t paccount_data = uds_account_data_create();
*  uds_account_data_set_id(account_data,1000);
*  uds_account_data_set_name(account_data,"My C Account");
*  uds_account_data_set_icon(account_data,"ic_account.png");
*  uds_account_data_set_target_name(account_data,"com.example.service");
*  if (0 != (retVal = uds_account_added(udsHandle, account_data)))
*  {
*            printf("uds_account_added failed with error %d \n", retVal);
*  }
* @endcode
* 3. Register Actions - Account based actions and context based actions on long selection of a list item
*  //Client service supported and defined actions on list items
*    typedef enum{
*      Read = 0x01<<0,
*      Unread = 0x01<<1,
*      FriendRequest = 0x01<<2
*    } ActionState;
*    uds_account_action_data_t account_action = uds_account_action_data_create();
*    AccountActionData aItem;
*    uds_account_action_data_set_action(account_action,"bb.action.SHARE");
*    uds_account_action_data_set_target(account_action,"UDSTestApp");
*    uds_account_action_data_set_type(account_action,"text/plain");
*    uds_account_action_data_set_title(account_action,"Status");
*    uds_account_action_data_set_image_source(account_action,"ic_status.png");
*    uds_account_action_data_set_placement(account_action,uds_placement_type_t::UDS_PLACEMENT_BAR);
*    if (UDS_SUCCESS!= (retVal = uds_register_account_action(udsHandle, 1000 , account_action)))
*    {
*        printf("uds_register_account_action failed with error %d\n", retVal);
*    }
*    uds_account_action_destroy(action_data);
*
*
*    uds_item_action_data_t item_action = uds_item_action_data_create();
*    uds_item_action_data_set_action(item_action,"bb.action.MARKREAD");
*    uds_item_action_data_set_target(item_action,"text/plain");
*    uds_item_action_data_set_title(item_action,"Mark Read");
*    uds_item_action_data_set_image_source(item_action,"ca_uds_read.png");
*    uds_item_action_data_set_mime_type(item_action,"plain/message");
*    uds_item_action_data_set_context_mask(item_action,Read);
*    if (UDS_SUCCESS!= (retVal = uds_register_item_context_action(udsHandle, 1000 , item_action)))
*    {
*        printf("uds_register_item_context_action failed with error %d\n", retVal);
*    }
*   uds_item_action_destroy(item_action);
*
* 4 Clients can add individual list items and categories
*
*@code
*   uds_inbox_item_data_t pInboxItem = uds_inbox_item_data_create();
*   uds_inbox_item_data_set_account_id(pInboxItem,1000);
*   uds_inbox_item_data_set_source_id(pInboxItem,"1");
*   uds_inbox_item_data_set_name(pInboxItem,"C Inbox Item Unread");
*   uds_inbox_item_data_set_description(pInboxItem,"C Subject Unread");
*   uds_inbox_item_data_set_icon(pInboxItem,"ca_uds_unread.png");
*   uds_inbox_item_data_set_mime_type(pInboxItem,"plain/message");
*   uds_inbox_item_data_set_unread_count(pInboxItem,1);
*   uds_inbox_item_data_set_total_count(pInboxItem,1);
*   uds_inbox_item_data_set_category_id(pInboxItem,1);
*   uds_inbox_item_data_set_timestamp(pInboxItem,1373405489000);
*   uds_inbox_item_data_set_context_state(pInboxItem,Read);
*   if (UDS_SUCCESS!= (retVal = uds_item_added(udsHandle, pInboxItem)))
*   {
*      printf("uds_item_added failed with error %d\n", retVal);
*   }
*   uds_inbox_item_data_destroy(pInboxItem);
*@endcode
*
*/

/**
 * @brief Primary handle used to communicate with HUB
 *
 */
typedef void* uds_context_t;

/**
 * @brief Indicates primary account key associated with the data
 *
 * @details This key is unique across the platform and is obtained using api in bbpim
 *
 */
typedef long long int uds_account_key_t;

/**
 * @brief Indicates category id of a category under an account
 *
 * @details An example of this key would be a folder id of a folder under a messaging account
 *
 */
typedef long long int uds_category_key_t;
/**
 * @brief Indicates a unique source id of a inbox list item
 *
 * @details This key is typically unique per account and is used to
 * represent a unique list item that was added using @c uds_item_added
 *
 */
typedef char* uds_source_key_t;

/**
 * @brief Indicates a unique server side sync id of a inbox list item
 *
 */
typedef char* uds_sync_key_t;

/**
 * @brief Indicates a data key associated with data that is added to hub
 *
 */
typedef long long int uds_data_key_t;

/**
 * @brief Data that represents account related data , this is used in
 * @c uds_account_added , Each account is represented as a tab in the man hub view
 */
typedef struct uds_account_data uds_account_data_t;

/**
 * @brief Data that represents list inbox item  related data , this is used in
 * @c uds_item_added, Each unqiue item is a list item in the main hub view and
 * the specific account view
 */
typedef struct uds_inbox_item_data uds_inbox_item_data_t;
/**
 * @brief Data that represents a Folder under an account , this is used in
 * @c uds_category_added
 */
typedef struct uds_category_data uds_category_data_t;
/**
 * @brief Data that represents account action for an account , this is used in
 * @c uds_register_account_action.
 * @details This action is added to Action bar on the client account view
 */
typedef struct uds_account_action_data uds_account_action_data_t;

/**
 * @brief Data that represents actions for a list item , this is used in
 * @c uds_register_item_action.
 * @details This action is added to context menu based on context state provided for a inbox item
 */
typedef struct uds_item_action_data uds_item_action_data_t;


/**
 * @brief Return Error codes for Client on api calls
 */
typedef enum{
    /**
     * @brief Indicates the operation succeeded
     */
    UDS_SUCCESS = 0,
    /**
     * @brief Indicates the operation failed
     */
    UDS_ERROR_FAILED = 501,
    /**
     * @brief Indicates client is disconnected from hub
     */
    UDS_ERROR_DISCONNECTED = 502,
    /**
     * @brief Indicates inbox item is invalid
     * @details Place holder - not supported
     */
    UDS_ERROR_INVALID_ITEM = 503,
    /**
     * @brief Indicates a operation is not supported
     * @details Place holder - not supported
     */
    UDS_ERROR_NOT_SUPPORTED = 504,
    /**
     * @brief Indicates an operation timed out
     */
    UDS_ERROR_TIMEOUT = 505,

    /**
     * @brief Indicates if a configuration already exists on the hub
     * @detail  Place holder - not supported
     */
    UDS_DUPLICATE_CONFIG = 601,

    /**
     * @brief Indicates if a service id is invalid
     * @detail This could happen if the client tries to add data
     * without registering first
     */
    UDS_INVALID_SERVICE_ID = 602,

    /**
     * @brief Indicates if an account id does not exists on the hub
     * @detail This could happen if the account id provided does not match
     * the one that was used by @c uds_account_added or if the account
     * does not exists on Hub
     */
    UDS_INVALID_ACCOUNT_ID = 603

}uds_error_code_t;

/**
 * @brief Return Registration on @c uds_register_client
 */
typedef enum {
    /**
     * @brief Indicates an unknown error , registration was not complete
     * @detail  Place holder - not supported
     */
    UDS_REGISTRATION_UNKNOWN = 0,
    /**
     * @brief Indicates if the registration was complete and if it was a new one
     * @detail This happens the very first time a client registers, or after an OTA upgrade
     * that resulted in a schema change on hub ,this code indicates to the client that it is
     * a fresh registration and so it should go ahead an add its data - account , items etc
     */
    UDS_REGISTRATION_NEW = 1,

    /**
     * @brief Indicates if the registration already exists
     * @detail This happens when the client restarts after a registration is already done
     */
    UDS_REGISTRATION_EXISTS = 2,

    /**
     * @brief Indicates an error , registration was not complete
     * @detail  Place holder - not supported
     */
    UDS_REGISTRATION_ERROR =3
}uds_registraion_code_t;


/**
 * @brief Different account status that can be registered with the HUB ,
 * account status is used for categorizing an account
 * as work, personal or hybrid
 */
typedef enum{
    /**
     * @brief Indicates if the account is enterprise
     */
    UDS_ACCOUNT_ENTERPRISE = 2,
    /**
     * @brief Indicates if the account is personal
     */
    UDS_ACCOUNT_PERSONAL = 8,
    /**
     * @brief Indicates if the account is hybrid
     */
    UDS_ACCOUNT_HYBRID = 64
}uds_account_status_t;

/**
 * @brief Different perimeter that can be associated with an item
 */
typedef enum {
    /**
     * @brief Indicates if the item belongs in enterprise perimeter
     * @details used only for hybrid accounts as items can belong to both perimters
     */
    UDS_PERIMETER_ENTERPRISE = 0x1,
    /**
     * @brief Indicates if the item belongs in personal perimeter
     */
    UDS_PERIMETER_PERSONAL   = 0x2
} uds_perimeter_type_t;


typedef enum {
    /* @brief Default value, typically In Over flow menu. */
    UDS_PLACEMENT_DEFAULT=0,
    /* @brief Specifies that the action should be placed in the Action menu only.
     *
     */
    UDS_PLACEMENT_OVERFLOW=1,
    /* @brief  Specifies that the action should be placed on the Action bar.
     * The action will also be placed in the Action menu.
     */
    UDS_PLACEMENT_BAR=2,
    /**
     * @brief Placement is fixed , for example delete/archive action
     */
    UDS_PLACEMENT_FIXED=3,
}uds_placement_type_t;

/**
* @brief Different account types that can be registered wit the HUB
* @details account type is used for grouping and ordering on hub account tab
* @warning setting this type does not guarantee placement order in main HUB tab
*/
typedef enum{
    /**
     * @brief Indicates account type notification
     */
    UDS_ACCOUNT_TYPE_NOTIFICATION = 2,
    /**
     * @brief Indicates account type sms/mms
     */
    UDS_ACCOUNT_TYPE_TEXT_MESSAGE = 3,
    /**
     * @brief Indicates social account
     */
    UDS_ACCOUNT_TYPE_SOCIAL = 5,
    /**
     * @brief Indicates IM  account
     */
    UDS_ACCOUNT_TYPE_IM = 6,
    /**
     * @brief Indicates other account
     */
    UDS_ACCOUNT_TYPE_OTHER = 11
} uds_account_type_t;


/**
 * @brief UDS Account data
 */

/**
  * @brief Creates a handle for account data
  */
uds_account_data_t *uds_account_data_create();
/**
  * @brief Deletes a handle for account data
  */
void uds_account_data_destroy(uds_account_data_t *inst);

/**
  * @brief Set account key for the account data
  * @param uds_account_data_t created using @c uds_account_data_create
  * @param uds_account_key_t unique account key obtained from the pim api
  *
  */
void uds_account_data_set_id(uds_account_data_t *account, uds_account_key_t id);
/**
  * @brief Set name for the account data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_account_added , or @c uds_account_updated
  * @param uds_account_data_t created using @c uds_account_data_create
  * @param name the label of the account tab on the hub for this account
  *
  */
void uds_account_data_set_name(uds_account_data_t *account, const char* name);

/**
  * @brief Set description for the account data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_account_added , or @c uds_account_updated
  * @param uds_account_data_t created using @c uds_account_data_create
  * @param account_desc the string that is under the main account label ,
  *  could be the account specific name like the user account name
  */
void uds_account_data_set_description(uds_account_data_t *account, const char* account_desc);

/**
  * @brief Set icon for the account data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_account_added , or @c uds_account_updated
  * @param uds_account_data_t created using @c uds_account_data_create
  * @param icon , the icon of the account tab on the hub for this account
  *
  */
void uds_account_data_set_icon(uds_account_data_t *account, const char* icon);

/**
  * @brief Set locked icon key for the account data
  * @details only required for UDS_ACCOUNT_ENTERPRISE and UDS_ACCOUNT_HYBRID account type
  * The string value passed in MUST remain valid , till the data
  * is used in  @c uds_account_added , or @c uds_account_updated
  * @param uds_account_data_t created using @c uds_account_data_create
  * @param locked_icon , the icon on the account tab when the perimeter is locked
  *
  */
void uds_account_data_set_locked_icon(uds_account_data_t *account, const char* locked_icon);

/**
  * @brief Set if compose is supported by the account data
  * @param uds_account_data_t created using @c uds_account_data_create
  * @param bool true if the account is to be supported on common compose in HUB view
  *
  */
void uds_account_data_set_supports_compose(uds_account_data_t *account, bool support_compose);


/**
  * @brief Set target name for the account data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_account_added , or @c uds_account_updated
  * @param uds_account_data_t created using @c uds_account_data_create
  * @param target_name , used as a generic target for all invokes related to this account
  *
  */
void uds_account_data_set_target_name(uds_account_data_t *account, const char* target_name);

/**
  * @brief Set compose icon for the account data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_account_added , or @c uds_account_updated
  * @param uds_account_data_t created using @c uds_account_data_create
  * @param compose_icon the colored icon used in common compose screen from HUB
  */
void uds_account_data_set_compose_icon(uds_account_data_t *account, const char* compose_icon);

/**
  * @brief Set type for the account data
  * @param uds_account_data_t created using @c uds_account_data_create
  * @param Type of the account
  */
void uds_account_data_set_type(uds_account_data_t *account, uds_account_type_t type);

/**
  * @brief Get account key for the account data
  * @param uds_account_data_t created using @c uds_account_data_create
  *
  * @return uds_account_key_t
  *
  */
uds_account_key_t uds_account_data_get_id(uds_account_data_t const *account);

/**
  * @brief Get name for the account data
  * @param uds_account_data_t created using @c uds_account_data_create
  *
  * @return name of the account
  *
  */
const char* uds_account_data_get_name(uds_account_data_t const *account);

/**
  * @brief Get description for the account data
  * @param uds_account_data_t created using @c uds_account_data_create
  *
  * @return account description
  *
  */
const char* uds_account_data_get_description(uds_account_data_t const *account);

/**
  * @brief Get icon for the account data
  * @param uds_account_data_t created using @c uds_account_data_create
  *
  * @return icon for the account
  *
  */
const char* uds_account_data_get_icon(uds_account_data_t const *account);

/**
  * @brief Get locked icon key for the account data
  * @param uds_account_data_t created using @c uds_account_data_create
  *
  * @return locked icon for the account
  *
  */
const char* uds_account_data_get_locked_icon(uds_account_data_t const *account);

/**
  * @brief Get if compose is supported by the account data
  * @param uds_account_data_t created using @c uds_account_data_create
  *
  * @return bool true if compose in common HUB view is supported
  *
  */
bool uds_account_data_get_supports_compose(uds_account_data_t const *account);

/**
  * @brief Set target name for the account data
  * @param uds_account_data_t created using @c uds_account_data_create
  *
  * @return default target name for this account
  *
  */
const char* uds_account_data_get_target_name(uds_account_data_t const *account);

/**
  * @brief Set compose icon for the account data
  * @param uds_account_data_t created using @c uds_account_data_create
  *
  * @return compose_icon
  */
const char* uds_account_data_get_compose_icon(uds_account_data_t const *account);

/**
  * @brief Get type for the account data
  * @param uds_account_data_t created using @c uds_account_data_create
  * @return Type of the account
  */
uds_account_type_t uds_account_data_get_type(uds_account_data_t const *account);


/**
 * @brief UDS Inbox Item data
 */

/**
  * @brief Creates a handle for inbox item data
  */
uds_inbox_item_data_t *uds_inbox_item_data_create();

/**
  * @brief Deletes a handle for inbox item data
  */
void uds_inbox_item_data_destroy(uds_inbox_item_data_t *inst);

/**
  * @brief Set account id for the inbox item data
  * @details based on this account key the item is added to the specific account tab
  * and on the common hub view
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param uds_account_key_t unique account key for the item
  *
  */
void uds_inbox_item_data_set_account_id(uds_inbox_item_data_t *inbox_item, uds_account_key_t account_id);

/**
  * @brief Set source id for the inbox item data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_item_added , or @c uds_item_updated
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param uds_source_key_t unique source id for the item
  *
  */
void uds_inbox_item_data_set_source_id(uds_inbox_item_data_t *inbox_item, uds_source_key_t source_id);

/**
  * @brief Set sync id for the inbox item data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_item_added , or @c uds_item_updated
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param uds_sync_key_t unique source id for the item
  *
  */
void uds_inbox_item_data_set_sync_id(uds_inbox_item_data_t *inbox_item, uds_sync_key_t sync_id);

/**
  * @brief Set category id for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param uds_category_key_t unique category id for the item
  *
  */
void uds_inbox_item_data_set_category_id(uds_inbox_item_data_t *inbox_item, uds_category_key_t category_id);

/**
  * @brief Set name id for the inbox item data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_item_added , or @c uds_item_updated
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param uds_source_key_t unique source id for the item
  * @details This is the string that is on the Top on the list item
  *
  */
void uds_inbox_item_data_set_name(uds_inbox_item_data_t *inbox_item, const char* name);

/**
  * @brief Set descritpio for the inbox item data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_item_added , or @c uds_item_updated
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param uds_source_key_t unique source id for the item
  * @details This is the string that is presented at the bottom of the list item,
  *  example subject of a message
  *
  */
void uds_inbox_item_data_set_description(uds_inbox_item_data_t *inbox_item, const char* description);

/**
  * @brief Set icon for the inbox item data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_item_added , or @c uds_item_updated
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param icon for the item
  * @details This icon is presented for the list item on the left
  *
  */
void uds_inbox_item_data_set_icon(uds_inbox_item_data_t *inbox_item, const char* icon);

/**
  * @brief Set mime type for the inbox item data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_item_added , or @c uds_item_updated
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param mime_type for the item
  *
  */
void uds_inbox_item_data_set_mime_type(uds_inbox_item_data_t *inbox_item, const char* mime_type);

/**
  * @brief Set user data for the inbox item data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_item_added , or @c uds_item_updated
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param user data , client specific user data
  *
  */
void uds_inbox_item_data_set_user_data(uds_inbox_item_data_t *inbox_item, const char* user_data);

/**
  * @brief Set extended data for the inbox item data
  * @details Used for any customization of the list item
  * The string value passed in MUST remain valid , till the data
  * is used in  @c uds_item_added , or @c uds_item_updated
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param extended data , client specific extended data
  *
  */
void uds_inbox_item_data_set_extended_data(uds_inbox_item_data_t *inbox_item, const char* extended_data);

/**
  * @brief Set timestamp for the inbox item data
  * @details Unix timestamp in ms
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param timestamp , determines the order in the list with most recent being on the top
  *
  */
void uds_inbox_item_data_set_timestamp(uds_inbox_item_data_t *inbox_item, long long int timestamp);

/**
  * @brief Set unread count for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param unread count , for a new unread item this will be greater than 0
  *
  */
void uds_inbox_item_data_set_unread_count(uds_inbox_item_data_t *inbox_item, int unread_count);

/**
  * @brief Set total count for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param total count, for an item representing a conversation this indicates the total messages in
  * the conversation
  *
  */
void uds_inbox_item_data_set_total_count(uds_inbox_item_data_t *inbox_item, int total_count);

/**
  * @brief Set perimeter for inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param perimeter, for UDS_ACCOUNT_HYBRID accounts , this determines if the any action
  * on this item is invoked in work or personal perimeter
  *
  */
void uds_inbox_item_data_set_perimeter(uds_inbox_item_data_t *inbox_item, uds_perimeter_type_t perimeter);

/**
  * @brief Set context state for inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param context state, used to populate context specific actions registered via
  * @c uds_register_item_context_action
  *
  */
void uds_inbox_item_data_set_context_state(uds_inbox_item_data_t *inbox_item, unsigned int context_state);

/**
  * @brief Set if notification for this item is enabled
  * @details this flag enables the client to suppress notifications for example during sync
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @param true if a notification is triggered to notification service
  *
  */
void uds_inbox_item_data_set_notification_state(uds_inbox_item_data_t *inbox_item, bool enabled);

/**
  * @brief Get account id for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return account id  for the item
  *
  */
uds_account_key_t uds_inbox_item_data_get_account_id(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get source id for the inbox item data
  * @param calid uds_inbox_item_data_t
  *
  * @return uds_source_key_t unique source id for the item
  *
  */
uds_source_key_t uds_inbox_item_data_get_source_id(uds_inbox_item_data_t const  *inbox_item);


/**
  * @brief Get sync id for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return sync id for the item
  *
  */
uds_sync_key_t uds_inbox_item_data_get_sync_id(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get category id for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return Category id for the item
  *
  */
uds_category_key_t uds_inbox_item_data_get_category_id(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get name for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return name id for the item
  *
  */
const char* uds_inbox_item_data_get_name(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get description for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return description id for the item
  *
  */
const char* uds_inbox_item_data_get_description(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get icon for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return icon id for the item
  *
  */
const char* uds_inbox_item_data_get_icon(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get mime type for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return mime type for the item
  *
  */
const char* uds_inbox_item_data_get_mime_type(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get user data for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return user datafor the item
  *
  */
const char* uds_inbox_item_data_get_user_data(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get extended data for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return extended data for the item
  *
  */
const char* uds_inbox_item_data_get_extended_data(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get timestamp for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return timestamp for the item in ms
  *
  */
long long int uds_inbox_item_data_get_timestamp(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get unread count for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return unread count for the item
  *
  */
int uds_inbox_item_data_get_unread_count(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get total count for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return total count for the item
  *
  */
int uds_inbox_item_data_get_total_count(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get perimeter  for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return perimeter for the item
  *
  */
uds_perimeter_type_t uds_inbox_item_data_get_perimeter(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get context state  for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return context state for the item
  *
  */
unsigned int uds_inbox_item_data_get_context_state(uds_inbox_item_data_t const  *inbox_item);

/**
  * @brief Get notification state  for the inbox item data
  * @param uds_inbox_item_data_t created using @c uds_inbox_item_data_create
  * @return true if notification is enabled for this item
  *
  */
bool uds_inbox_item_data_get_notification_state(uds_inbox_item_data_t const  *inbox_item);


/**
 * @brief UDS Category data
 */
/**
  * @brief Creates a handle for category data
  */
uds_category_data_t *uds_category_data_create();
/**
  * @brief Deletes a handle for category data
  */
void uds_category_data_destroy(uds_category_data_t *inst);

/**
  * @brief Set id for the category data
  * @param uds_category_data_t created using @c uds_category_data_create
  * @param unique id for the category
  */
void uds_category_data_set_id(uds_category_data_t *category, uds_category_key_t id);

/**
  * @brief Set parent id for the category data
  * @param uds_category_data_t created using @c uds_category_data_create
  * @param unique parent id for the category
  */
void uds_category_data_set_parent_id(uds_category_data_t *category, uds_category_key_t parent_id);

/**
  * @brief Set account id for the category data
  * @param uds_category_data_t created using @c uds_category_data_create
  * @param account id for the category
  */
void uds_category_data_set_account_id(uds_category_data_t *category, uds_account_key_t account_id);

/**
  * @brief Set category type for the category data
  * @param uds_category_data_t created using @c uds_category_data_create
  * @param type for the category
  */
void uds_category_data_set_type(uds_category_data_t *category, int type);

/**
  * @brief Set category name for the category data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_category_added , or @c uds_category_updated
  * @param uds_category_data_t created using @c uds_category_data_create
  * @param name for the category
  */
void uds_category_data_set_name(uds_category_data_t *category, const char* name);


/**
  * @brief Get id for the category data
  * @param uds_category_data_t created using @c uds_category_data_create
  * @return id for the category
  */
uds_category_key_t uds_category_data_get_id(uds_category_data_t const *category);

/**
  * @brief Get parent id for the category data
  * @param uds_category_data_t created using @c uds_category_data_create
  * @return parent id for the category
  */
uds_category_key_t uds_category_data_get_parent_id(uds_category_data_t const *category);

/**
  * @brief Set account id for the category data
  * @param uds_category_data_t created using @c uds_category_data_create
  * @return account id for the category
  */
uds_account_key_t uds_category_data_get_account_id(uds_category_data_t *category);

/**
  * @brief Set category type for the category data
  * @param uds_category_data_t created using @c uds_category_data_create
  * @return type for the category
  */
int uds_category_data_get_type(uds_category_data_t const *category);

/**
  * @brief Set category name for the category data
  * @param uds_category_data_t created using @c uds_category_data_create
  * @return name for the category
  */
const char* uds_category_data_get_name(uds_category_data_t const *category);


/**
 * UDS Account action data
 */

/**
  * @brief Creates a handle for account action data
  */
uds_account_action_data_t *uds_account_action_data_create();
/**
  * @brief Destroy a handle for account action data
  */
void uds_account_action_data_destroy(uds_account_action_data_t *inst);

/**
  * @brief Set action for the account action data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_register_account_action , or @c uds_update_account_action
  * @param account_action_t created using @c uds_account_action_data_create
  * @param Action string for the action registered , example "bb.action.STATUS"
  */
void uds_account_action_data_set_action(uds_account_action_data_t *account_action, const char* action);

/**
  * @brief Set target for the account action data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_register_account_action , or @c uds_update_account_action
  * @param account_action_t created using @c uds_account_action_data_create
  * @param Target used for invoking the action registered
  */
void uds_account_action_data_set_target(uds_account_action_data_t *account_action, const char* invoke_target);

/**
  * @brief Set target type for the account action data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_register_account_action , or @c uds_update_account_action
  * @param account_action_t created using @c uds_account_action_data_create
  * @param Target type used for invoking the action registered , example "card.composer for a compose card"
  * "service" for a service type
  */
void uds_account_action_data_set_type(uds_account_action_data_t *account_action, const char* target_type);

/**
  * @brief Set title for the account action data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_register_account_action , or @c uds_update_account_action
  * @param account_action_t created using @c uds_account_action_data_create
  * @param Title for the action registered
  */
void uds_account_action_data_set_title(uds_account_action_data_t *account_action, const char* title);

/**
  * @brief Set image source for the account action data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_register_account_action , or @c uds_update_account_action
  * @param account_action_t created using @c uds_account_action_data_create
  * @param Image source for the action registered
  */
void uds_account_action_data_set_image_source(uds_account_action_data_t *account_action, const char* image_source);

/**
  * @brief Set Mime type for the account action data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_register_account_action , or @c uds_update_account_action
  * @param account_action_t created using @c uds_account_action_data_create
  * @param Mime type for the action registered
  */
void uds_account_action_data_set_mime_type(uds_account_action_data_t *account_action, const char* mime_type);

/**
  * @brief Set Placement for the account action data
  * @param account_action_t created using @c uds_account_action_data_create
  * @param Placement type for the action registered , based on this parameter the
  * action icon will appear on the bar or the over flow of the action tool bar
  */
void uds_account_action_data_set_placement(uds_account_action_data_t *account_action, uds_placement_type_t placement);

/**
  * @brief Get action for the account action data
  * @param account_action_t created using @c uds_account_action_data_create
  * @return action string
  */
const char* uds_account_action_data_get_action(uds_account_action_data_t const *account_action);

/**
  * @brief Get target for the account action data
  * @param account_action_t created using @c uds_account_action_data_create
  * @return Target used for invoking the action registered
  */
const char* uds_account_action_data_get_target(uds_account_action_data_t const *account_action);

/**
  * @brief Get target type for the account action data
  * @param account_action_t created using @c uds_account_action_data_create
  * @return Target type used for invoking the action registered
  */
const char* uds_account_action_data_get_type(uds_account_action_data_t *account_action);

/**
  * @brief Get title for the account action data
  * @param account_action_t created using @c uds_account_action_data_create
  * @return Title for the action registered
  */
const char* uds_account_action_data_get_title(uds_account_action_data_t const *account_action);

/**
  * @brief Get image source for the account action data
  * @param account_action_t created using @c uds_account_action_data_create
  * @return Image source for the action registered
  */
const char* uds_account_action_data_get_image_source(uds_account_action_data_t *account_action);

/**
  * @brief Get Mime type for the account action data
  * @param account_action_t created using @c uds_account_action_data_create
  * @return Mime type for the action registered
  */
const char* uds_account_action_data_get_mime_type(uds_account_action_data_t const *account_action);

/**
  * @brief Get Placement for the account action data
  * @param account_action_t created using @c uds_account_action_data_create
  * @return Placement for the action registered
  */
uds_placement_type_t uds_account_action_data_get_placement(uds_account_action_data_t *account_action);


/**
 * UDS Item action data
 */


/**
  * @brief Creates a handle for item action data
  */
uds_item_action_data_t *uds_item_action_data_create();
/**
  * @brief Destroy a handle for item action data
  */
void uds_item_action_data_destroy(uds_item_action_data_t *inst);

/**
  * @brief Set action for the account action data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_register_item_action , or @c uds_update_item_action
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @param Action string for the action registered , example bb.action.STATUS
  */
void uds_item_action_data_set_action(uds_item_action_data_t *item_action, const char* action);

/**
  * @brief Set target for the item action data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_register_item_action , or @c uds_update_item_action
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @param Target used for invoking the action registered
  */
void uds_item_action_data_set_target(uds_item_action_data_t *item_action, const char* invokeTarget);

/**
  * @brief Set target type for the item action data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_register_item_action , or @c uds_update_item_action
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @param Target type used for invoking the action registered , example "card.composer for a compose card"
  * "service" for a service type
  */
void uds_item_action_data_set_type(uds_item_action_data_t *item_action, const char* targetType);

/**
  * @brief Set title for the item action data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_register_item_action , or @c uds_update_item_action
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @param Title for the action registered
  */
void uds_item_action_data_set_title(uds_item_action_data_t *item_action, const char* title);

/**
  * @brief Set image source for the item action data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_register_item_action , or @c uds_update_item_action
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @param Image source for the action registered
  */
void uds_item_action_data_set_image_source(uds_item_action_data_t *item_action, const char* imageSource);

/**
  * @brief Set Mime type for the item action data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_register_item_action , or @c uds_update_item_action
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @param Mime type for the action registered
  */
void uds_item_action_data_set_mime_type(uds_item_action_data_t *item_action, const char* mime_type);

/**
  * @brief Set Placement for the item action data
  * @details The string value passed in MUST remain valid , till the data
  * is used in  @c uds_register_item_action , or @c uds_update_item_action
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @param Placement type for the action registered , based on this paramter the
  * action icon will appear on the bar or the over flow of the action tool bar
  */
void uds_item_action_data_set_placement(uds_item_action_data_t *item_action, uds_placement_type_t placement);

/**
  * @brief Set Context state mask for the item action data
  * @details Bitmask state that is used for populating item specific actions -
  * Client designates a bit for each possible actions that can be performed on a item - read , unread etc ) ,
  * so while registering item specific actions using @uds_register_item_context_action, you would specify a mask
  * that would be used to query the bit state of the item's context action state to populate the context menus
  * see @c uds_register_item_context_action
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  */
void uds_item_action_data_set_context_mask(uds_item_action_data_t *item_action, unsigned int mask);

/**
  * @brief Get action for the item action data
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @return action string for the item action registered
  */
const char* uds_item_action_data_get_action(uds_item_action_data_t const *item_action);

/**
  * @brief Get target for the item action data
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @return Target used for invoking the item action registered
  */
const char* uds_item_action_data_get_target(uds_item_action_data_t const *item_action);

/**
  * @brief Get target type for the item action data
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @return Target type used for invoking the item action registered
  */
const char* uds_item_action_data_get_type(uds_item_action_data_t const *item_action);

/**
  * @brief Get title for the item action data
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @return Title for the item action registered
  */
const char* uds_item_action_data_get_title(uds_item_action_data_t const *item_action);

/**
  * @brief Get image source for the item action data
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @return Image source for the item action registered
  */
const char* uds_item_action_data_get_image_source(uds_item_action_data_t const *item_action);

/**
  * @brief Get Mime type for the item action data
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @return Mime type for the item action registered
  */
const char* uds_item_action_data_get_mime_type(uds_item_action_data_t const *item_action);

/**
  * @brief Get Placement for the item action data
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @return Placement type for the item action registered
  */
uds_placement_type_t uds_item_action_data_get_placement(uds_item_action_data_t const *item_action);

/**
  * @brief Get Context mask for the item action data
  * @param uds_item_action_data_t created using @c uds_account_action_data_create
  * @return Mask for the item action registered
  */
unsigned int uds_item_action_data_get_context_mask(uds_item_action_data_t const *item_action);



/**
 * UnifiedDataSourceC Library can be used in following way:
 *
 * In synchronous mode - all calls will block until error or response from server
 *
 * uds_init - will open a connection of this library with UIB, async = FALSE
 *
 * uds_register_client - will register the caller with UIB and will provide a unique serviceId along with its status with UIB
 *                     - if client was previously registered, it will get RegistrationExists, it its a new connection, caller
 *                     - will get RegistrationNew.  If its a new registration, caller must send all its information to UIB,
 *                     - if its an existing registration, caller can choose to send only items that are new since last sync with UIB
 *
 * [optional] uds_get_service_id - this call should be made only after uds_register_client is UDS_SUCCESSful
 *
 * [optional] uds_get_service_status - this call should be made only after uds_register_client is UDS_SUCCESSful
 *
 * uds_account_added   - this call will create an account within UIB, caller can create as many accounts as they wish from within
 *                     - same registration.  Each account is uniquely represented with a separate icon in UIB
 *
 * uds_category_added  - optional, if caller wishes to add folders/categories for items
 *
 * uds_item_added      - this call will add an inbox list item within UIB
 *
 * uds_item_updated    - if inbox item changes its state, for ex. icon change, status read/unread changes etc.
 *
 * uds_item_removed    - to remove an inbox item
 *
 *
 * In asynchronous mode - all calls will return immediately after sending command to the server
 *
 * uds_init - will open a connection of this library with UIB, async = TRUE
 *
 * uds_register_client - will register the caller with UIB and will provide a unique serviceId along with its status with UIB
 *                     - if client was previously registered, it will get RegistrationExists, it its a new connection, caller
 *                     - will get RegistrationNew.  If its a new registration, caller must send all its information to UIB,
 *                     - if its an existing registration, caller can choose to send only items that are new since last sync with UIB
 *
 * [optional] uds_wait_for_response - on possibly separate thread to block until there is response from server
 *
 * uds_get_response    - to fetch and parse the response from server
 *
 * [optional] uds_get_service_id - this call should be made only after uds_register_client and uds_get_response has been called once.
 *
 * [optional] uds_get_service_status - this call should be made only after uds_register_client and uds_get_response has been called once.
 *
 * uds_account_added   - this call will create an account within UIB, caller can create as many accounts as they wish from within
 *                     - same registration.  Each account is uniquely represented with a separate icon in UIB
 *
 * uds_wait_for_response, uds_get_response    - to fetch and parse response
 *
 * uds_category_added  - optional, if caller wishes to add folders/categories for items
 *
 * uds_wait_for_response, uds_get_response    - to fetch and parse response
 *
 * uds_item_added      - this call will add an inbox list item within UIB
 *
 * uds_wait_for_response, uds_get_response    - to fetch and parse response
 *
 * uds_item_updated    - if inbox item changes its state, for ex. icon change, status read/unread changes etc.
 *
 * uds_wait_for_response, uds_get_response    - to fetch and parse response
 *
 * uds_item_removed    - to remove an inbox item
 *
 * uds_wait_for_response, uds_get_response    - to fetch and parse response
 *
 */



/**
 * Initializes and opens a connection to Unified Inbox.
 * @param handle - caller must allocate uds_context_t and provide valid pointer to the handle, which is filled
 * by the library with valid handle on UDS_SUCCESS.
 * @param async - this boolean defines whether you want to run in asynchronous mode or sychronous mode
 *                in async mode, all calls will return immediately after sending the command to server without waiting for response
 *                caller has to make sure to call uds_wait_for_response on separate thread and then uds_get_response to get response
 *                in sync mode, call will only return after UDS_SUCCESSfully getting response from server and will block until then.
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_init(uds_context_t* pHandle, bool async);

/**
 * Closes the connection to Unified Inbox.
 * @param Resources allocated within the provided handle are released by the library.
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_close(uds_context_t* pHandle);

/**
 * Registers the caller as a client entity with Unified Inbox.
 *
 * @param pServiceURL - a uniquely identified service URL to be registered
 * @param pLibPath - library path of any module required to be loaded by Unified Inbox Application
 * @param pAssetPath - relative path of assets located within UIB
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_register_client(uds_context_t handle, const char* pServiceURL, const char* pLibPath, const char* pAssetPath);

/**
 * Unregisters the caller as a client entity with Unified Inbox.
 *
 * @param handle associated with the client registration.
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_unregister_client(uds_context_t handle);

/**
 * Adds the provided account to Unified Inbox.  If UDS_SUCCESSful, a unique account icon will show up in UIB.
 *
 * @param handle associated with client registration
 * @param AccountData representing all the information required to register and display an account in UIB.
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_account_added(uds_context_t handle, uds_account_data_t* pAccount);

/**
 * Updates the existing account in Unified Inbox.
 *
 * @param handle associated with client registration
 * @param AccountData representing all the information required to register and display an account in UIB.
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_account_updated(uds_context_t handle, uds_account_data_t* pAccount);

/**
 * Removes the existing account in Unified Inbox.
 *
 * @param handle associated with client registration
 * @param accountId of an existing account in UIB
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_account_removed(uds_context_t handle, uds_account_key_t accountId);

/**
 * Adds an Inbox Item in UIB associated with an existing account.  If UDS_SUCCESSful, an Inbox Item will show up in UIB
 * under the right account and/or category.
 *
 * @param handle associated with client registration
 * @param pItem - an InboxItemData filled with all the required information.
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_item_added(uds_context_t handle, const uds_inbox_item_data_t* pItem);

/**
 * Updates an existing Inbox Item in Unified Inbox.
 *
 * @param handle associated with client registration
 * @param pItem - an InboxItemData filled with all the required information.
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_item_updated(uds_context_t handle, const uds_inbox_item_data_t* pItem);

/**
 * Removes an existing Inbox Item in Unified Inbox.
 *
 * @param handle associated with client registration
 * @param accountId - account associated with Inbox Item.
 * @param pSourceId - a unique source id of the item to be removed.
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_item_removed(uds_context_t handle, uds_account_key_t accountId, const uds_source_key_t pSourceId);


/**
 * Remove Inbox Items in Unified Inbox with the specified mimetype.
 *
 * @param handle associated with client registration
 * @param accountId - account associated with Inbox Item.
 * @param mimetype - mimetype of the items to be removed.
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_items_removed_mimetype(uds_context_t handle, uds_account_key_t accountId, const char *mimetype);

/**
 * Adds a category within a previously registered account in Unified Inbox.
 *
 * @param handle associated with client registration
 * @param category data for the category to be added.
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_category_added(uds_context_t handle, const uds_category_data_t* pCategory);

/**
 * Updates an existing category in Unified Inbox
 *
 * @param handle associated with client registration
 * @param category data for the category to be updated.
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_category_updated(uds_context_t handle, const uds_category_data_t* pCategory);

/**
 * Removes an existing category from Unified Inbox account.
 *
 * @param handle associated with client registration
 * @param accountId of the account associated with category
 * @param a unique categoryId of the category to be removed.
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_category_removed(uds_context_t handle, uds_account_key_t accountId, uds_category_key_t categoryId);

/**
 * Waits and blocks the call until there is a response from server or until timeout.
 *
 * @param handle associated with client registration
 * @param timeout time to wait in milliseconds to block
 *
 * @return TRUE if there is response, FALSE on timeout
 */
bool uds_wait_for_response(uds_context_t handle, unsigned long timeout);

/**
 * Reads and parses the response from connected server for previously executed command
 *
 * @param handle associated with client registration
 *
 * @return UDS_SUCCESS on UDS_SUCCESS, non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_get_response(uds_context_t handle);

/**
 * Returns the associated service id of this client's registration with server.
 * Caller should have had UDS_SUCCESS with uds_register_client in synchronous more, or uds_get_response in async mode before this call.
 *
 * @param handle associated with client registration
 *
 * @return serviceId
 */
int uds_get_service_id(uds_context_t handle);

/**
 * Returns the associated service state of this client's registration with server.
 * Caller should have had UDS_SUCCESS with uds_register_client in synchronous more, or uds_get_response in async mode before this call.
 *
 * @param handle associated with client registration
 *
 * @return status
 */
int uds_get_service_status(uds_context_t handle);


/**
 * Registers the an Account action ( toolbar ) for a specific account view registered with Hub
 *
 * @param handle associated with client registration
 * @param accountId of an existing account in UIB
 * @param AccountActionData - Data that defines the account action with action,target,assetpath,etc
 *
 * @code
 * uds_account_action_data_t action_data = uds_item_action_data_create();
 * uds_account_action_data_set_action(account_action,"bb.action.STATUS");
 * uds_account_action_data_set_target(account_action,"UDSTestApp");
 * uds_account_action_data_set_type(account_action,"");
 * uds_account_action_data_set_title(account_action,"Status");
 * uds_account_action_data_set_image_source(account_action,"ic_status.png");
 * uds_account_action_data_set_mime_type(account_action,"text/plain");
 * uds_account_action_data_set_placement(account_action,UDS_PLACEMENT_BAR);
 * if (UDS_SUCCESS!= (retVal = uds_register_account_action(udsHandle, 1 , account_action)))
 * {
 *       printf("uds_register_account_action failed with error %d\n", retVal);
 * }
 * @endcode
 *
 * @return UDS_SUCCESS or non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_register_account_action(uds_context_t handle, uds_account_key_t accountId, const uds_account_action_data_t* pAccountAction);


/**
 * Update an Account action ( toolbar ) for a specific account view registered with Hub , this can happen on locale changes
 *
 * @param handle associated with client registration
 * @param accountId of an existing account in UIB
 * @param AccountActionData - Data that defines the account action with action,target,assetpath,etc
 * @return UDS_SUCCESS or non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_update_account_action(uds_context_t handle, uds_account_key_t accountId, const uds_account_action_data_t* pAccountAction);


/**
 * Register an item context action, the data populates Context Menu on selection on Hub
 *
 * @param handle associated with client registration
 * @param accountId of an existing account in UIB
 * @param ItemActionData - Data that defines the item specific action - depends on the state of the item
 * @return UDS_SUCCESS or non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 * @code
 * Globally defined Context Actions by the client
 * typedef enum{
 *  ReadAction = 0x01<<0,
 *  UnreadReadAction = 0x01<<1,
 *  AcceptAction = 0x01<<2
 * }ActionState;
 *
 *  uds_item_action_data_t *item_action = uds_item_action_data_create();
 *  uds_item_action_data_set_action(item_action,"bb.action.ACCEPT");
 *  uds_item_action_data_set_target(item_action,"UDSTestApp");
 *  uds_item_action_data_set_type(item_action,"service");
 *  uds_item_action_data_set_title(item_action,"Accept Request");
 *  uds_item_action_data_set_image_source(item_action,"uds_accept.png");
 *  uds_item_action_data_set_mime_type(item_action,mime_type);
 *  uds_item_action_data_set_placement(item_action,"application/vnd.blackberry.socialconnect.UDSTestApp.notification");
 *  uds_item_action_data_set_context_mask(item_action,AcceptAction);
 * if (UDS_SUCCESS!= (retVal = uds_register_item_context_action(udsHandle, 1 , item_action)))
 * {
 *   printf("uds_register_item_context_action failed with error %d\n", retVal);
 * }
 *
*/
int uds_register_item_context_action(uds_context_t handle, uds_account_key_t accountId, const uds_item_action_data_t* pItem);

/**
 * Update an item context action, this can happen on locale changes
 *
 * @param handle associated with client registration
 * @param accountId of an existing account in UIB
 * @param ItemActionData - Data that defines the item specific action - depends on the state of the item
 * @return UDS_SUCCESS or non-zero error code on failure.  See uds_error_code_t or errno.h for details.
 */
int uds_update_item_context_action(uds_context_t handle, uds_account_key_t accountId, const uds_item_action_data_t* pItem);


__END_DECLS

#endif /* UNIFIED_DATASOURCE_C_H_ */
