/********************************************************************\

   Name:         mxml.h
   Created by:   Stefan Ritt

   Contents:     Header file for mxml.c

   $Log$
   Revision 1.1  2005/03/01 23:48:18  ritt
   Implemented MXML for password file

\********************************************************************/

/*------------------------------------------------------------------*/

#define MXML_NAME_LENGTH 64

typedef struct {
   int  fh;
   int  level;
   BOOL element_is_open;
   BOOL data_was_written;
   char **stack;
} MXML_WRITER;

typedef struct mxml_struct *PMXML_NODE;

typedef struct mxml_struct {
   char       name[MXML_NAME_LENGTH];  // name of element    <[name]>[value]</[name]>
   char       *value;                  // value of element
   int        n_attributes;            // list of attributes
   char       *attribute_name;
   char       **attribute_value;
   int        line_number;             // line number for source file
   PMXML_NODE parent;                  // pointer to parent element
   int        n_children;              // list of children
   PMXML_NODE child;
} MXML_NODE;

/*------------------------------------------------------------------*/

MXML_WRITER *mxml_open_document(const char *file_name);
BOOL mxml_start_element(MXML_WRITER *writer, const char *name);
BOOL mxml_end_element(MXML_WRITER *writer); 
BOOL mxml_write_attribute(MXML_WRITER *writer, const char *name, const char *value);
BOOL mxml_write_value(MXML_WRITER *writer, const char *value);
BOOL mxml_close_document(MXML_WRITER *writer);

int mxml_get_number_of_children(PMXML_NODE pnode);
PMXML_NODE mxml_find_node(PMXML_NODE tree, char *xml_path);
char *mxml_get_value(PMXML_NODE pnode);
char *mxml_get_attribute(PMXML_NODE pnode, char *name);

BOOL mxml_add_attribute(PMXML_NODE pnode, char *attrib_name, char *attrib_value);
PMXML_NODE mxml_add_node(PMXML_NODE parent, char *node_name, char *value);

BOOL mxml_replace_node_name(PMXML_NODE pnode, char *new_name);
BOOL mxml_replace_node_value(PMXML_NODE pnode, char *value);
BOOL mxml_replace_subvalue(PMXML_NODE pnode, char *name, char *value);
BOOL mxml_replace_attribute_name(PMXML_NODE pnode, char *old_name, char *new_name);
BOOL mxml_replace_attribute_value(PMXML_NODE pnode, char *attrib_name, char *attrib_value);

BOOL mxml_delete_node(PMXML_NODE pnode);
BOOL mxml_delete_attribute(PMXML_NODE, char *attrib_name);

PMXML_NODE mxml_create_root_node();
PMXML_NODE mxml_parse_file(char *file_name, char *error, int error_size);
BOOL mxml_write_tree(char *file_name, PMXML_NODE tree);
void mxml_free_tree(PMXML_NODE tree);

/*------------------------------------------------------------------*/
