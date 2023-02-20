#include "../kernel/drivers/serial/serial.h"

struct objc_module {
    unsigned long version;      /* Version of the Module data
                   structure.  */
    unsigned long size;         /* sizeof(Module) according to the
                   compiler - only used to sanity check
                   that it matches sizeof(Module)
                   according to the runtime.  */
    const char *name;           /* Name of the file used to compile the
                   module - not set by modern compilers
                   for security reasons.  */
    struct objc_symtab *symtab; /* Pointer to the Symtab of the module.
                   The Symtab holds an array of pointers
                   to the classes and categories defined
                   in the module. */
};

//extern struct __attribute__ ((section (".text._OBJC_Module"))) objc_module* _OBJC_Module ;

struct objc_class
{
    struct objc_class *class_pointer;
    struct objc_class *super_class;
    const char *name;
    long version;
    unsigned long info;
    long instance_size;

    void *ivars;
    void *method_list;
    void *dtable;
    struct objc_class *subclass_list;
    struct objc_class *silbing_class;

    void *protocol_list;
    void *gc_object_type;
};

struct objc_selector
{
    const char *sel_id;
    const char *sel_types;
};

void what()
{
    serial_port port = {
        .port = SERIAL_COM1};

    serial_port_write_string(&port, "kurwa\n");
}

void *objc_msg_lookup(struct objc_class *class, struct objc_selector *sel, ...)
{
    serial_port port = {
        .port = SERIAL_COM1};

    const char *id = sel->sel_id;
    //struct objc_module* module = _OBJC_Module;

    if (class->name == NULL)
    {
        serial_port_write_string(&port, "a\n");
        return 0;
    }

    serial_port_write_string(&port, "objc_msg_lookup: ");
    serial_port_write_string(&port, id);
    serial_port_write_string(&port, "\n");

    return what;
}

void *objc_get_class(const char *name)
{
    serial_port port = {
        .port = SERIAL_COM1};

    serial_port_write_string(&port, "objc_get_class: ");
    serial_port_write_string(&port, name);
    serial_port_write_string(&port, "\n");
    return 0;
}

void __objc_exec_class(struct objc_module *module) {
    serial_port port = {
        .port = SERIAL_COM1};

    unsigned long version = module->version;
    void* things = module->symtab;

    serial_port_write_string(&port, "__objc_exec_class: ");
    serial_port_write_string(&port, module->name);
    serial_port_write_string(&port, "\n");
}