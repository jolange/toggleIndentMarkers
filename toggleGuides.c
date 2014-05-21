#include <geanyplugin.h>
#include <editor.h>
GeanyPlugin*    geany_plugin;
GeanyData*      geany_data;
GeanyFunctions* geany_functions;
static gboolean s_bSpacesVisible;

PLUGIN_VERSION_CHECK(211) // TODO check
PLUGIN_SET_INFO(
   "Toggle Guides",
   "Toggles indentation guides, white space visibility, "
   "(TODO:) line endings.",
   "0.1", "Johannes Lange");

static GtkWidget *main_menu_item = NULL;
static GtkToolItem *toolbar_item = NULL;
static void toggle_visibility(GtkMenuItem *menuitem, gpointer gdata)
{
   /* TODO for all documents?
    * http://www.geany.org/manual/reference/document_8h.html, documents_array */
   GeanyEditor* editor = document_get_current()->editor;
   ScintillaObject* 	sci = editor->sci;

   /* toggle indent guides visibility */
   editor_set_indentation_guides(editor);

   /* toggle white space visibility */
   sci_set_visible_white_spaces(sci, s_bSpacesVisible);
   /*sci_set_visible_eols(sci, s_bSpacesVisible);*/
   s_bSpacesVisible = !s_bSpacesVisible;
}
void plugin_init(GeanyData *data)
{
   /* TODO
    * read user prefs
    * options what to toggle
    * option for toolbar/menu items
    */
   s_bSpacesVisible = FALSE;
   main_menu_item = gtk_menu_item_new_with_mnemonic("TG");
   toolbar_item = gtk_tool_button_new(NULL,"TG");
   gtk_widget_show(main_menu_item);
   /*gtk_container_add(GTK_CONTAINER(geany->main_widgets->tools_menu),
   main_menu_item);*/
   plugin_add_toolbar_item (geany_plugin,GTK_TOOL_ITEM(toolbar_item));
   gtk_widget_show(GTK_WIDGET(toolbar_item));
   g_signal_connect(main_menu_item, "activate",
   G_CALLBACK(toggle_visibility), NULL);
   g_signal_connect(toolbar_item, "clicked",
   G_CALLBACK(toggle_visibility), NULL);
}

void plugin_cleanup(void)
{
   gtk_widget_destroy(main_menu_item);
   /* TODO is this right? */
   gtk_widget_destroy(GTK_WIDGET(toolbar_item));
   /*gtk_widget_destroy(toolbar_item);*/
}

/* remove
PluginCallback plugin_callbacks[] =
{
	{ NULL, NULL, FALSE, NULL }
};
*/
