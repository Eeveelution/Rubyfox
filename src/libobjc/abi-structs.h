#ifndef __OBJC_MAIN_H_
#define __OBJC_MAIN_H_

typedef struct {
    //Selector String, i.e. "writeString:stringLength:serialPort:"
    const char *sel_id;
    //Objective-C Type Encoding
    //v8@0:4 = void at offset 8 (return type), id (@) at offset 0 (implicit self), selector (:) at offset 4
    //for what it's worth you can ignore the numbers and just read the types, as the offsets are
    //there because of the Motorolla 68000 Calling Convention which was heavily stack based.
    const char *sel_types;
} objc_selector;

typedef struct objc_method_list objc_method_list;

typedef struct objc_class {
    struct objc_class *class_pointer;
    struct objc_class *super_class;

    const char *name;
    long version;
    unsigned long info;
    long instance_size;

    //TODO: implement structs
    void *ivars;
    objc_method_list* method_list;
    void *dtable;
    struct objc_class *subclass_list;
    struct objc_class *silbing_class;

    //TODO: implement structs
    void *protocol_list;
    void *gc_object_type;
} objc_class;

typedef struct objc_object {
    objc_class* class_ptr;
} *id;

typedef id (*IMP)(id, objc_selector*, ...); 

typedef struct {
    //objc_selector* selector;
    const char* method_name;
    const char* method_types;

    IMP method_implementation;
} objc_method;

typedef struct objc_method_list {
    struct objc_method_list* next;

    int method_count;

    objc_method method_list[1];
} objc_method_list;

typedef struct objc_category {
    const char* name;
    const char* class_name;

    objc_method_list* instance_method_list;
    objc_method_list* class_method_list;

    //TODO: implement struct
    void* protocol_list;
} objc_category;

typedef struct objc_symbol_table {
    unsigned long unused;

    /// @brief Table of Selectors that are referenced in this module; 
    /// List is terminated with sel_id == NULL && sel_types == NULL
    objc_selector* referenced_selectors[1];

    /// @brief Number of defined Classes
    unsigned short class_count;
    /// @brief Number of defined Categories
    unsigned short category_count;

    void* class_category_definitions[1];
} objc_symbol_table;

typedef struct objc_module {
    unsigned long version; 
    unsigned long size;
    const char* name; 
    objc_symbol_table* symtab;
} objc_module;

#endif