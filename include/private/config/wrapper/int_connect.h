/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2023 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** @file
 * A wrapper for connecting to a host with specific connection characteristics.
 * The functions return int connection handles.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_INT_CONNECT_H
#  define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_INT_CONNECT_H

#  include "private/config.h"

/* definition of config_int_connect */
#  ifdef HAVE_GETADDRINFO
#    include "private/config/have_getaddrinfo.h"
#    define config_int_connect getaddrinfo_int_connect
#  elif SUPPORT_GETHOSTBYNAME
#    include "private/config/gethostbyname_supported.h"
#    define config_int_connect gethostbyname_int_connect
#  endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_INT_CONNECT_H */
