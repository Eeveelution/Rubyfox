#include "../kernel/drivers/serial/serial.h"
#include "../kernel/string.h"

#include "abi-structs.h"

objc_module* current_module = NULL;

void *objc_msg_lookup(objc_class *class, objc_selector *sel, ...)
{
    serial_port port = {
        .port = SERIAL_COM1
    };

    const char *id = sel->sel_id;

    if (class->name == NULL)
    {
        serial_port_write_string(&port, "a\n");
        return 0;
    }

    serial_port_write_string(&port, "objc_msg_lookup: ");
    serial_port_write_string(&port, id);
    serial_port_write_string(&port, "\n");

    for(short i = 0; i != class->method_list->method_count; i++) {
        objc_method current = class->method_list->method_list[i];

        const char* currentSel = current.method_name.name;
        const char* compareSel = sel->sel_id;

        if(strncmp(currentSel, compareSel, 255) == 1) {
            return current.method_implementation;
        }
    }

    return 0;
}

objc_class* objc_get_class(const char *name)
{
    objc_module* module = current_module;

    serial_port port = {
        .port = SERIAL_COM1
    };

    serial_port_write_string(&port, "objc_get_class: ");
    serial_port_write_string(&port, name);
    serial_port_write_string(&port, "\n");

    for(int i = 0; i != module->symtab->class_count; i++) {
        objc_class current_class = module->symtab->class_category_definitions[i].class_ptr;

        if(strncmp(current_class.name, name, 255) == 1) {
            return &module->symtab->class_category_definitions[i].class_ptr;
        }
    }

    return 0;
}

void __objc_exec_class(objc_module *module) {
    current_module = module;

    serial_port port = {
        .port = SERIAL_COM1};

    unsigned long version = module->version;
    void* things = module->symtab;

    serial_port_write_string(&port, "__objc_exec_class: ");
    serial_port_write_string(&port, module->name);
    serial_port_write_string(&port, "\n");
}