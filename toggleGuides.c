#include <geanyplugin.h>
#include <editor.h>

GeanyPlugin*    geany_plugin;
GeanyData*      geany_data;
GeanyFunctions* geany_functions;

PLUGIN_VERSION_CHECK(211) // TODO check
PLUGIN_SET_INFO(
   "Toggle Indent Markers",
   "Toggles indentation and white space markers visibility, "
   "(TODO:) line endings.",
   "0.1", "Johannes Lange");

static gboolean s_bSpacesVisible;
static GtkToolItem *toolbar_item = NULL;

static void toggle_visibility(void)
{
   /* debug:
   if (s_bSpacesVisible)
      dialogs_show_msgbox(GTK_MESSAGE_INFO, "vis");
   else
      dialogs_show_msgbox(GTK_MESSAGE_INFO, "no vis");
   */

   s_bSpacesVisible = !s_bSpacesVisible;
   /* TODO for all documents?
    * http://www.geany.org/manual/reference/document_8h.html, documents_array */
   GeanyEditor* editor = document_get_current()->editor;
   ScintillaObject*	sci = editor->sci;

   /* toggle white space visibility */
   sci_set_visible_white_spaces(sci, s_bSpacesVisible);
   /*sci_set_visible_eols(sci, s_bSpacesVisible);*/
}

void plugin_init(GeanyData *data)
{
   /* TODO
    * read user prefs
    * options what to toggle
    */

   // TODO consider document change
   s_bSpacesVisible = geany_data->editor_prefs->show_white_space;
   //s_bTabsVisible = data->editor_prefs->show_indent_guide;

   toolbar_item = gtk_tool_button_new(NULL,"TIM");

   plugin_add_toolbar_item (geany_plugin,GTK_TOOL_ITEM(toolbar_item));
   gtk_widget_show(GTK_WIDGET(toolbar_item));

   g_signal_connect(toolbar_item, "clicked", G_CALLBACK(toggle_visibility), NULL);
}

void plugin_cleanup(void)
{
   gtk_widget_destroy(GTK_WIDGET(toolbar_item));
}

/* remove
PluginCallback plugin_callbacks[] =
{
	{ NULL, NULL, FALSE, NULL }
};
*/
