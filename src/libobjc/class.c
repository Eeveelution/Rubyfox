//#include "../kernel/drivers/serial/serial.h"
#include <string.h>

#include "abi-structs.h"

objc_module* current_module = NULL;

/// @brief Used by the Objective-C Compiler to look where to route function calls
/// @param class Receiver of the message
/// @param sel Message Selector
/// @param Arguments
/// @return Method Implementation
IMP objc_msg_lookup(objc_class *class, objc_selector *sel) {
    objc_method_list* method_list = class->class_pointer->method_list;

    // In case that there is no base class,
    // Pull methods straight from the class method list instead
    if(class->class_pointer == NULL || method_list == NULL) {
        method_list = class->method_list;
    }

    for(short i = 0; i != method_list->method_count; i++) {
        objc_method current = method_list->method_list[i];

        const char* currentSel = current.method_name;
        const char* compareSel = sel->sel_id;

        if(strncmp(currentSel, compareSel, 255) == 1) {
            return current.method_implementation;
        }
    }

    return 0;
}

/// @brief Used by the Objective-C Compiler to retrieve classes
/// @param name Name of the class
/// @return Class or 0 if none is found.
objc_class* objc_get_class(const char *name)
{
    objc_module* module = current_module;

    objc_category* unused_category = module->symtab->class_category_definitions[0 + module->symtab->class_count];

    for(int i = 0; i != module->symtab->class_count; i++) {
        objc_class* current_class = module->symtab->class_category_definitions[i];

        if(strncmp(current_class->name, name, 255) == 1) {
            return module->symtab->class_category_definitions[i];
        }
    }

    return 0;
}

/// @brief This is executed by __objc_gnu_init and gives you the Objective-C Module.
/// You need this as this contains all the Compiled Class definitions, Protocols, etc.
/// @param module Objective-C Module
void __objc_exec_class(objc_module *module) {
    current_module = module;

    objc_selector* sel;

    int i = 0;

    while(1) {
        sel = module->symtab->referenced_selectors[i];

        void* sel_id = sel->sel_id;
        const char* sel_types = sel->sel_types;

        if(sel_id == NULL && sel_types == NULL) {
            break;
        }

        i++;
    }
}