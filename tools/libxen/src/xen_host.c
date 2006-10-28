/*
 * Copyright (c) 2006, XenSource Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */


#include <stddef.h>
#include <stdlib.h>

#include "xen_common.h"
#include "xen_host.h"
#include "xen_host_cpu.h"
#include "xen_internal.h"
#include "xen_pif.h"
#include "xen_string_string_map.h"
#include "xen_vm.h"


XEN_FREE(xen_host)
XEN_SET_ALLOC_FREE(xen_host)
XEN_ALLOC(xen_host_record)
XEN_SET_ALLOC_FREE(xen_host_record)
XEN_ALLOC(xen_host_record_opt)
XEN_RECORD_OPT_FREE(xen_host)
XEN_SET_ALLOC_FREE(xen_host_record_opt)


static const struct_member xen_host_record_struct_members[] =
    {
        { .key = "uuid",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, uuid) },
        { .key = "name_label",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, name_label) },
        { .key = "name_description",
          .type = &abstract_type_string,
          .offset = offsetof(xen_host_record, name_description) },
        { .key = "software_version",
          .type = &abstract_type_string_string_map,
          .offset = offsetof(xen_host_record, software_version) },
        { .key = "resident_VMs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_host_record, resident_vms) },
        { .key = "PIFs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_host_record, pifs) },
        { .key = "host_CPUs",
          .type = &abstract_type_ref_set,
          .offset = offsetof(xen_host_record, host_cpus) }
    };

const abstract_type xen_host_record_abstract_type_ =
    {
       .typename = STRUCT,
       .struct_size = sizeof(xen_host_record),
       .member_count =
           sizeof(xen_host_record_struct_members) / sizeof(struct_member),
       .members = xen_host_record_struct_members
    };


void
xen_host_record_free(xen_host_record *record)
{
    free(record->handle);
    free(record->uuid);
    free(record->name_label);
    free(record->name_description);
    xen_string_string_map_free(record->software_version);
    xen_vm_record_opt_set_free(record->resident_vms);
    xen_pif_record_opt_set_free(record->pifs);
    xen_host_cpu_record_opt_set_free(record->host_cpus);
    free(record);
}


bool
xen_host_get_record(xen_session *session, xen_host_record **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = xen_host_record_abstract_type_;

    *result = NULL;
    XEN_CALL_("host.get_record");

    if (session->ok)
    {
       (*result)->handle = xen_strdup_((*result)->uuid);
    }

    return session->ok;
}


bool
xen_host_get_by_uuid(xen_session *session, xen_host *result, char *uuid)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = uuid }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_by_uuid");
    return session->ok;
}


bool
xen_host_create(xen_session *session, xen_host *result, xen_host_record *record)
{
    abstract_value param_values[] =
        {
            { .type = &xen_host_record_abstract_type_,
              .u.struct_val = record }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.create");
    return session->ok;
}


bool
xen_host_get_by_name_label(xen_session *session, xen_host *result, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_by_name_label");
    return session->ok;
}


bool
xen_host_get_name_label(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_name_label");
    return session->ok;
}


bool
xen_host_get_name_description(xen_session *session, char **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string;

    *result = NULL;
    XEN_CALL_("host.get_name_description");
    return session->ok;
}


bool
xen_host_get_software_version(xen_session *session, xen_string_string_map **result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_string_map;

    *result = NULL;
    XEN_CALL_("host.get_software_version");
    return session->ok;
}


bool
xen_host_get_resident_vms(xen_session *session, xen_vm *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_resident_vms");
    return session->ok;
}


bool
xen_host_get_pifs(xen_session *session, xen_pif *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_pifs");
    return session->ok;
}


bool
xen_host_get_host_cpus(xen_session *session, xen_host_cpu *result, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    XEN_CALL_("host.get_host_cpus");
    return session->ok;
}


bool
xen_host_set_name_label(xen_session *session, xen_host xen_host, char *label)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = xen_host },
            { .type = &abstract_type_string,
              .u.string_val = label }
        };

    xen_call_(session, "host.set_name_label", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_set_name_description(xen_session *session, xen_host xen_host, char *description)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = xen_host },
            { .type = &abstract_type_string,
              .u.string_val = description }
        };

    xen_call_(session, "host.set_name_description", param_values, 2, NULL, NULL);
    return session->ok;
}


bool
xen_host_disable(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.disable", param_values, 1, NULL, NULL);
    return session->ok;
}


bool
xen_host_enable(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.enable", param_values, 1, NULL, NULL);
    return session->ok;
}


bool
xen_host_shutdown(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.shutdown", param_values, 1, NULL, NULL);
    return session->ok;
}


bool
xen_host_reboot(xen_session *session, xen_host host)
{
    abstract_value param_values[] =
        {
            { .type = &abstract_type_string,
              .u.string_val = host }
        };

    xen_call_(session, "host.reboot", param_values, 1, NULL, NULL);
    return session->ok;
}


bool
xen_host_get_all(xen_session *session, xen_host *result)
{

    abstract_type result_type = abstract_type_string_set;

    *result = NULL;
    xen_call_(session, "host.get_all", NULL, 0, &result_type, result);
    return session->ok;
}


bool
xen_host_get_uuid(xen_session *session, char **result, xen_host host)
{
    *result = session->ok ? xen_strdup_((char *)host) : NULL;
    return session->ok;
}
