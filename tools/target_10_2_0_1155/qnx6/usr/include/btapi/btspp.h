/*
 * $QNXLicenseC:
 * Copyright 2012, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software. Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef BTSPP_H_
#define BTSPP_H_

/**
 * @file btspp.h
 *
 * @brief Functions to provide Bluetooth Serial Port (SPP) Protocol
 *        communication
 *
 * This file defines functions to work with Bluetooth. Communication via
 * Bluetooth uses SPP.
 */

#include <unistd.h>

__BEGIN_DECLS

/**
 * @brief Initialize the resources required for the Bluetooth library
 * @details It is necessary to call this function before you use any other
 *          functions in the library. If you call this function successfully,
 *          call the @c bt_spp_deinit() function when your application has
 *          finished using the Bluetooth Serial Port Profile (SPP) communication
 *          functionality.
 *
 * @return @c 0 when initialization is successful, @c -1 with the @c errno
 *         value set otherwise. An @c errno of @c ENOMEM indicates that there was
 *         insufficient memory to initialize resources. If the @c errno is set
 *         to any other value than what is listed, a system error has occurred.
 */
int bt_spp_init();

/**
 * @brief Clean up resources used by the library
 * @details This function cleans up resources initialized by the @c
 *          bt_spp_init() function after all connections are closed by the user.
 *          The @c bt_spp_deinit() function will not close any active
 *          connection and an attempt to call this function while there are
 *          active connections will return -1 with the @c errno set to @c EBUSY.
 *
 *          Call this function after your application has finished using the
 *          Bluetooth Serial Port Profile (SPP) communication functionality and
 *          after you have successfully called the @c bt_spp_init() function.
 *
 *          You do not need to call the @c bt_spp_deinit() function if a call to
 *          the @c bt_spp_init() function has failed.
 *
 * @return @c 0 is returned when initialization is successful, @c -1 with the
 *         @c errno value set as @c EBUSY otherwise. @c EBUSY indicates that
 *         there are open SPP connections.
 */
int bt_spp_deinit();

/**
 * @brief Create a Serial Port Profile (SPP) connection to a service on a remote
 *        Bluetooth device (server)
 * @details The connection can be opened in non-blocking or blocking mode.
 *          After you successfully call this function, and when your application
 *          is finished with the file descriptor that is returned from this
 *          function, call the @c bt_spp_close() function to clean up resources.
 *
 * @param addr The remote Bluetooth device (server) address. The address is in
 *             the following format: 2:2:2:2:2:2, where each digit indicates
 *             the number of hexadecimal digits. For example: <tt>
 *             00:11:22:33:AA:BB</tt>.
 * @param service_uuid The Universally Unique Identifier (UUID) or the name of
 *                     the service to connect to. If this parameter represents
 *                     the UUID, it must be the service ID defined by the
 *                     developer, not the Service Class ID assigned by the
 *                     Bluetooth organization. For example, the SPP profile has
 *                     a 4-digit Service Class ID of @c 0x1101. A developer can
 *                     create multiple services for this service class, and must
 *                     define a unique service ID for each of the services. This
 *                     function searches for the intended service using the input
 *                     UUID when the input matches a supported service ID format.
 *                     If @c service_uuid does not match any supported UUID format,
 *                     this argument is considered to contain the service name,
 *                     which has a maximal length of 50 including the terminating
 *                     NULL character. Then the search for the service is done
 *                     by service name and generic SPP attributes.
 *                     If this argument represents the service ID, it must be in
 *                     one of the following formats:
 *                     - "0x1101": search by generic SPP attributes
 *                     - "0x1101:<uuid>": search by UUID \<uuid\>
 *                     - "<uuid>": search by UUID \<uuid\>
 *                     where \<uuid\> is in <8-4-4-4-12> format, in which each
 *                     digit indicates the number of hexadecimal digits. For
 *                     example, a valid service ID can be:
 *                     - @c "00001101-1111-2222-3333-444444444444": search by
 *                       service UUID @c "00001101-1111-2222-3333-444444444444"
 *                     - <tt> "0x1101:00001101-1111-2222-3333-444444444444"</tt>:
 *                       search by service UUID
 *                       @c "00001101-1111-2222-3333-444444444444"
 *                     - @c "0x1101": search by generic SPP attributes
 *                     - @c "0x1102": search by service name @c "0x1102" and
 *                       generic SPP attributes
 *                     - <tt>"3rd party SPP service"</tt>: search by service
 *                       name <tt>"3rd party SPP service"</tt> and generic SPP
 *                       attributes
 * @param nonblock A flag that specifies whether to open a mount point of the
 *                 connection in non-blocking mode. A value of @c true means
 *                 opening the connection in non-blocking mode.
 * @return The mount point file descriptor if a connection has been successfully
 *         created, @c -1 with the @c errno set otherwise. The @c errno can be
 *         set to one of the following values when @c -1 is returned. If the @c
 *         errno is set to any other value than the following, a system error
 *         has occurred.
 *         - @c EINVAL: Invalid arguments were specified.
 *         - @c EPERM: The @c bt_spp_init() function has not been called or has
 *                     failed.
 *         - @c ENONMEM: There is insufficient memory to allocate to complete
 *                       the function.
 *         - @c ESRVRFAULT: The operation was aborted by the user.
 *         - @c EBADMSG: There was an error parsing the incoming message.
 *         - @c EMLINK: A connection to the same service on the same device has
 *                      already been established.
 *         - @c ENODATA: A failure occurred because an error occurred on the
 *                       stack.
 */
int bt_spp_open(char *addr, char *service_uuid, bool nonblock);

/**
 * @brief Open a Serial Port Profile (SPP) server
 * @details This function registers a service record and starts a thread to
 *          listen for incoming connections. When an incoming connection is
 *          accepted, a callback gets called with a valid mount point file
 *          descriptor as the argument. If the connection is not accepted, the
 *          callback returns an invalid file descriptor (-1).
 *          You cannot register two services with the same UUID even if the
 *          service names are different.  Before you attempt to call this
 *          function again using the same UUID,  you must call the
 *          @c bt_spp_close_server() function. If you do not call the
 *          @c bt_spp_close_server() function, subsequent attempts to open
 *          an SPP server will fail.
 *
 * @param service_name The name of the service to appear in the service's
 *                     Service Discovery Protocol (SDP) record. The maximal
 *                     length is 50 including the terminating NULL character.
 *                     If this argument is empty or set to @c NULL, the default
 *                     service name that appears in the SDP record is "SPP Service".
 * @param service_uuid The Universally Unique Identifier (UUID) of the service
 *                     to register. Note that this is the service ID defined
 *                     by the developer, not the Service Class ID assigned by the
 *                     Bluetooth organization. For example, the SPP profile has
 *                     a 4-digit Service Class ID of @c 0x1101. A developer can
 *                     create multiple services for this service class, and must
 *                     define a unique service ID for each of the services. The
 *                     service ID must be in the following format: 8-4-4-4-12,
 *                     where each digit indicates the number of hexadecimal
 *                     digits. For example, a valid service ID can be:
 *                     @c 00001101-1111-2222-3333-444444444444.
 *                     UUID @c 00001101-0000-1000-8000-00805f9b34fb is reserved
 *                     by the Bluetooth organization as the Service Class ID for
 *                     SPP. We do not recommend that you use it on the server
 *                     side as the service ID for a newly defined service, as it
 *                     cannot guarantee the uniqueness of the service.
 * @param nonblock A flag that specifies whether to open a mount point of the
 *                 connection in non-blocking mode. A value of @c true will
 *                 open the connection in non-blocking mode.
 * @param param  The user's parameter as the first argument of the returned
 *               callback.
 * @param callback A pointer to a valid callback function that provides the
 *                 mount point file descriptor. The mount point file descriptor
 *                 is available when the SPP server has accepted incoming
 *                 connections. In case of a failure, the file descriptor
 *                 returns with a value of @c -1 and @c errno is set with the
 *                 reason.
 *                 @b Note: The callback that you specify in the @c callback
 *                 argument, should not be used for any CPU or memory intensive
 *                 tasks, because it would block the threads required for
 *                 delivering messages from stack.
 * @return @c 0 if the operation is successful, @c -1 otherwise. Ensure that you
 *         call the @c bt_spp_close_server() function if the call to the @c
 *         bt_spp_open_server() succeeded, even if the callback returned a file
 *         descriptor of @c -1. The @c errno can be set to one of the following
 *         values when @c -1 is returned. If the @c errno is set to any other
 *         value than the following, a system error has occurred.
 *         - @c EINVAL: Invalid arguments were specified.
 *         - @c EPERM: The @c bt_spp_init() function has not been called or has
 *                     failed.
 *         - @c ENONMEM: There is insufficient memory to allocate to complete
 *                       the function.
 *         - @c ESRVRFAULT: The operation was aborted by the user.
 *         - @c EBADMSG: There was an error parsing the incoming message.
 *         - @c EMLINK: A connection to the same service on the same device has
 *                      already been established.
 *         - @c ENODATA: A failure occurred because an error occurred on the
 *                       stack.
 */
int bt_spp_open_server(char *service_name, char *service_uuid, bool nonblock, void (*callback)(long param,int fd), long param);

/**
 * @brief Disconnect the link and deregister the Serial Port Profile (SPP) server
 * @details This function requires that you use the Universally Unique
 *          Identifier (UUID) that you used to register the server.
 *          You open the server using the @c bt_spp_open_server()
 *          function.
 *
 * @param service_uuid The UUID of the service to deregister.
 * @return  @c 0 when the link is disconnected and the SPP server is deregistered
 *          successfully, @c -1 with @c errno set otherwise. The @c errno can be
 *          set to one of the following values:
 *          - @c EINVAL: An invalid argument was specified.
 *          - @c EPERM: The @c bt_spp_init() function has not been called or has
 *                     failed.
 */
int bt_spp_close_server(char *service_uuid);

/**
 * @brief Disconnect from the service associated with the file descriptor
 * @details This function closes the client side SPP connection opened with 
 *          the @c bt_spp_open() function. Ensure that you call this function 
 *          after your application has finished using the file descriptor
 *          from a successful call to the @c bt_spp_open() function.
 *
 *          Do not call this function if you started a session with the
 *          @c bt_spp_open_server() function, even if the callback returned a
 *          valid file descriptor.
 *
 * @param fd The mount point file descriptor returned by the @c bt_spp_open()
 *           function.
 * @return  @c 0 when the service is successfully disconnected, @c -1 with the
 *          @c errno set otherwise. The @c errno can be set to one of the
 *          following values:
 *          - @c EPERM: The @c bt_spp_init() function has not been called or has
 *                      failed.
 *          - @c EBADF: An invalid file descriptor is passed to the function.
 */
int bt_spp_close(int fd);

/**
 * @brief Get the address of a remote device
 * @details This function returns the address of a remote device for the
 *         connection identified by the file descriptor.
 * @param fd The mount point file descriptor returned by the @c bt_spp_open()
 *         function or through the @c bt_spp_open_server() function.
 * @param addr The 18-byte buffer allocated by a user in which the address is
 *             returned.
 * @return @c 0 if the address is returned, @c -1 otherwise, with @c errno
 *         set to one of the following values:
 *         - @c EINVAL: @c addr is NULL or too short
 *         - @c EPERM: The @c bt_spp_init() function has not been called or has
 *                     failed
 *         - @c EBADF: An invalid file descriptor is passed to the function.
 */
int bt_spp_get_address(int fd, char *addr);

__END_DECLS

#endif /* BTSPP_H_ */

#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )
