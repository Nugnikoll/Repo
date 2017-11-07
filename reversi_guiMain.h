/***************************************************************
 * Name:      reversi_guiMain.h
 * Purpose:   Defines Application Frame
 * Author:    Rick (1300012743@pku.edu.cn)
 * Created:   2016-04-16
 * Copyright: Rick ()
 * License:
 **************************************************************/

#ifndef REVERSI_GUIMAIN_H
#define REVERSI_GUIMAIN_H

//(*Headers(reversi_guiFrame)
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)
#include <wx/treectrl.h>
#include <wx/filedlg.h>

class reversi_guiFrame: public wxFrame
{
    public:

        reversi_guiFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~reversi_guiFrame();

    private:

        //(*Handlers(reversi_guiFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnClose1(wxCloseEvent& event);
        void on_panel_board_paint(wxPaintEvent& event);
        void on_panel_board_leftdown(wxMouseEvent& event);
        void on_text_input_textenter(wxCommandEvent& event);
        void Onbutton_startClick(wxCommandEvent& event);
        //*)
		void on_start(wxCommandEvent& event);
		void on_undo(wxCommandEvent& event);
		void on_redo(wxCommandEvent& event);
		void on_load(wxCommandEvent& event);
		void on_clear_log(wxCommandEvent& event);
		void on_clear_term(wxCommandEvent& event);
		void on_clear_all(wxCommandEvent& event);
		void on_transform(wxCommandEvent& event);
		void on_eval(wxCommandEvent& event);
		void on_menu_alg(wxCommandEvent& event);
		void on_menu_level(wxCommandEvent& event);
		void on_context_menu(wxContextMenuEvent& event);
		void on_tree_item_select(wxTreeEvent& event);
		void on_choice_player(wxCommandEvent& event);

        //(*Identifiers(reversi_guiFrame)
        static const long id_panel_board;
        static const long id_text_label;
        static const long id_label_black;
        static const long id_choice_black;
        static const long id_label_white;
        static const long id_choice_white;
        static const long id_button_start;
        static const long id_panel_note;
        static const long id_text_term;
        static const long id_text_log;
        static const long id_book_tree;
        static const long id_notebook;
        static const long id_text_input;
        static const long id_panel_base;
        static const long id_menu_new;
        static const long id_menu_load;
        static const long id_menu_save;
        static const long id_menu_quit;
        static const long id_menu_undo;
        static const long id_menu_redo;
        static const long id_menu_mirror_h;
        static const long id_menu_mirror_v;
        static const long id_menu_reflect;
        static const long id_menu_rotate_r;
        static const long id_menu_rotate_l;
        static const long id_menu_reverse;
        static const long id_menu_trans;
        static const long id_menu_eval;
        static const long id_menu_clear_log;
        static const long id_menu_clear_term;
        static const long id_menu_clear;
        static const long id_menu_alg_rnd;
        static const long id_menu_alg_ab;
        static const long id_menu_alg_pvs;
        static const long id_menu_alg_trans;
        static const long id_menu_alg_kill;
        static const long id_menu_alg_mtdf;
        static const long id_menu_alg_ids;
        static const long id_menu_alg_ptn;
        static const long id_menu_alg_mpc;
        static const long id_menu_alg;
        static const long id_menu_level1;
        static const long id_menu_level2;
        static const long id_menu_level3;
        static const long id_menu_level4;
        static const long id_menu_level5;
        static const long id_menu_level6;
        static const long id_menu_level7;
        static const long id_menu_level8;
        static const long id_menu_level9;
        static const long id_menu_level10;
        static const long id_menu_level;
        static const long id_menu_about;
        static const long id_statusbar;
        //*)

        //(*Declarations(reversi_guiFrame)
        wxMenuItem* menu_level1;
        wxMenuItem* menu_level6;
        wxMenu* menu_set;
        wxMenuItem* menu_alg_mtdf;
        wxMenuItem* menu_save;
        wxStatusBar* statusbar;
        wxMenuItem* menu_redo;
        wxMenuItem* menu_clear_term;
        wxMenuItem* menu_rotate_l;
        wxMenuItem* menu_new;
        wxPanel* panel_base;
        wxMenuItem* menu_reverse;
        wxButton* button_start;
        wxTextCtrl* text_term;
        wxMenu* menu_clear;
        wxMenu* menu_trans;
        wxNotebook* notebook;
        wxMenu* menu_alg;
        wxMenuItem* menu_alg_kill;
        wxChoice* choice_white;
        wxTextCtrl* text_input;
        wxMenuItem* menu_undo;
        wxMenuItem* menu_level4;
        wxMenuItem* menu_level8;
        wxMenuItem* menu_reflect;
        wxMenuItem* menu_alg_ptn;
        wxBoxSizer* BoxSizer2;
        wxTreeCtrl* book_tree;
        wxMenuItem* menu_mirror_v;
        wxMenuItem* menu_alg_trans;
        wxMenu* menu_edit;
        wxMenu* menu_level;
        wxStaticText* text_label;
        wxMenuItem* menu_alg_mpc;
        wxMenuItem* menu_level9;
        wxPanel* panel_note;
        wxMenuItem* menu_level10;
        wxMenuItem* menu_load;
        wxMenuItem* menu_clear_log;
        wxMenuItem* menu_mirror_h;
        wxMenuItem* menu_alg_rnd;
        wxBoxSizer* BoxSizer1;
        wxTextCtrl* text_log;
        wxMenuItem* menu_level7;
        wxPanel* panel_board;
        wxMenuItem* menu_eval;
        wxMenuItem* menu_level3;
        wxMenuItem* menu_level5;
        wxStaticText* label_black;
        wxMenuItem* menu_level2;
        wxChoice* choice_black;
        wxMenuItem* menu_rotate_r;
        wxMenuItem* menu_alg_ids;
        wxStaticText* label_white;
        wxMenuItem* menu_alg_pvs;
        wxMenuItem* menu_alg_ab;
        //*)

        DECLARE_EVENT_TABLE()
};
 
#endif // REVERSI_GUIMAIN_H
