//
// Created by karina on 13/06/19.
//

#include<stdio.h>
#include<string.h>
#include <gtk/gtk.h>

GtkWidget *fixed,*window;
GtkWidget *bckgrnd_wid;
GtkWidget *label;


int timer;

int score=0,hit=0,miss=0, lives = 3;

//*************************
GtkWidget *mario_wid, *donkey, *barrel_normal, *barrel_freefall, *barrel_mix;
int x_pos=0;
int y_pos=500;
int mario_tag=0;

int x_cord = 105;
int y_cord = 55;

int x_cord_free = 105;
int y_cord_free = 55;

int forward = 0;
int forward_free = 0;

GtkWidget *xpm_create( GtkWidget *parent,gchar *xpm_filename)
{
    GtkWidget *box1;
    GtkWidget *label;
    GtkWidget *pixmapwid;
    GdkPixmap *pixmap;
    GdkBitmap *mask;
    GtkStyle *style;
    style = gtk_widget_get_style(parent);
    pixmap = gdk_pixmap_create_from_xpm (parent->window, &mask,
                                         &style->bg[GTK_STATE_NORMAL],
                                         xpm_filename);
    pixmapwid = gtk_pixmap_new (pixmap, mask);
    return(pixmapwid);
}

/*--------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------
*/

int move_barrel_normal(GtkWidget *data)
{
    if(x_cord < 2)
    {
        forward = 0;
        y_cord = 55;
        x_cord = 105;

        gtk_fixed_put (GTK_FIXED (fixed), barrel_normal , x_cord, y_cord);
    }

    if(forward == 0){
        if(x_cord > 870 && 54 < y_cord && y_cord < 215 ){
            if(210 < y_cord && y_cord < 215)
                forward = 1;
            y_cord += 2;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_normal, x_cord, y_cord);
        }
        else if(x_cord > 870 && 380 < y_cord && y_cord < 530 ){
            if(528 < y_cord && y_cord < 530)
                forward = 1;
            y_cord += 2;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_normal, x_cord, y_cord);
        }
        else {
            x_cord += 2;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_normal, x_cord, y_cord);
        }
        return TRUE;
    } //backward
    else{
        if(x_cord < 100 && 209 < y_cord && y_cord < 380 ){
            if(378 < y_cord && y_cord < 380)
                forward = 0;
            y_cord += 2;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_normal, x_cord, y_cord);
        }
        else {
            x_cord -= 2;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_normal, x_cord, y_cord);
        }
        return TRUE;
    }


}


int move_barrel_freefall(GtkWidget *data)
{
    if(x_cord_free > 1000)
    {
        forward_free = 0;
        y_cord_free = 55;
        x_cord_free = 105;

        gtk_fixed_put (GTK_FIXED (fixed), barrel_freefall , x_cord_free, y_cord_free);
    }

    if(forward_free == 0){
        if(x_cord_free > 870 && 54 < y_cord_free && y_cord_free < 215 ){
            if(210 < y_cord_free && y_cord_free < 215)
                forward_free = 1;
            y_cord_free += 2;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_freefall, x_cord_free, y_cord_free);
        }
        else if(x_cord_free > 870 && 380 < y_cord_free && y_cord_free < 530 ){
            if(528 < y_cord_free && y_cord_free < 530)
                forward_free = 1;
            y_cord_free += 2;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_freefall, x_cord_free, y_cord_free);
        }
        else {
            x_cord_free += 2;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_freefall, x_cord_free, y_cord_free);
        }
        return TRUE;
    } //backward
    else{
        if(x_cord_free < 300 && 209 < y_cord_free && y_cord_free < 530 ){
            if(528 < y_cord_free && y_cord_free < 530)
                forward_free = 0;
            y_cord_free += 2;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_freefall, x_cord_free, y_cord_free);
        }
        else {
            x_cord_free -= 2;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_freefall, x_cord_free, y_cord_free);
        }
        return TRUE;
    }

}

int move_mario_right(GtkWidget *data)
{
    x_pos+=15;
    gtk_fixed_move (GTK_FIXED (fixed), data , x_pos, y_pos);
    g_message("%s, %d","XPOS: ",x_pos);
    g_message("%s, %d","YPOS: ",y_pos);
    //x=720 Escalera
    //x=945 Final
    return FALSE;
}
int move_mario_left(GtkWidget *data)
{
    x_pos-=15;
    gtk_fixed_move (GTK_FIXED (fixed), data , x_pos, y_pos);
    g_message("%s, %d","XPOS: ",x_pos);
    g_message("%s, %d","YPOS: ",y_pos);
    return FALSE;
}
int move_mario_up(GtkWidget *data)
{
    y_pos-=15;
    gtk_fixed_move (GTK_FIXED (fixed), data , x_pos, y_pos);
    g_message("%s, %d","XPOS: ",x_pos);
    g_message("%s, %d","YPOS: ",y_pos);
    return FALSE;
}
int move_mario_down(GtkWidget *data)
{
    y_pos+=15;
    gtk_fixed_move (GTK_FIXED (fixed), data , x_pos, y_pos);
    g_message("%s, %d","XPOS: ",x_pos);
    g_message("%s, %d","YPOS: ",y_pos);
    return FALSE;
}

//Metodo encargado de leer las entradas del teclado
gint key_press_cb(GtkWidget *widget, GdkEventKey *kevent, gpointer data)  {
    GtkWidget *btn = (GtkWidget *)data;

    if(kevent->type == GDK_KEY_PRESS)  {
        //g_message("%d, %c;", kevent->keyval, kevent->keyval);
        if(kevent->keyval==65363){
            g_message("%s","RIGHT");
            if(x_pos<=945){
                if(y_pos==500||y_pos==335){
                    mario_tag = gtk_timeout_add (20, move_mario_right, data);
                }
            }
        }
        if(kevent->keyval==65361){
            g_message("%s","LEFT");
            if(x_pos>=0){
                if(y_pos==500||y_pos==335){
                    mario_tag = gtk_timeout_add (20, move_mario_left, data);
                }
            }
        }
        if(kevent->keyval==65364){
            g_message("%s","DOWN");
            if((x_pos==705&&y_pos<500&&y_pos>=335)||(x_pos==390&&y_pos<335&&y_pos>=185)||(x_pos==300&&y_pos>=335&&y_pos<=410)){
                mario_tag = gtk_timeout_add (20, move_mario_down, data);
            }
        }
        if(kevent->keyval==65362){
            g_message("%s","UP");
            //Escaleras
            if((x_pos==705&&y_pos>335)||(x_pos==390&&y_pos<=335&&y_pos>=200)||(x_pos==300&&y_pos>=350&&y_pos<=425)){
                mario_tag = gtk_timeout_add (20, move_mario_up, data);
            }
        }
        if(kevent->keyval==32){
            g_message("%s","SPACE");
        }
    } g_signal_emit_by_name(G_OBJECT(widget), "clicked", NULL);
    return TRUE;
}
//**************************************************************




void set_score()
{
    char score_arr[5],point[12];
    sprintf (score_arr, "%d", (int) score);
    char *lab="SCORE : ";
    strcpy(point,lab);
    strcat(point,score_arr);
    gtk_label_set(GTK_LABEL(label),&point);
}

void restart(GtkWidget *wid, GtkWidget *data)
{
    gtk_widget_destroy(data);
    score=0;
    set_score();
    x_pos=0;
    y_pos=5000;
//timer = gtk_timeout_add (10, move_balloon, balloon_wid);
}
void game_over()
{
    gtk_timeout_remove (timer);
    GtkWidget *pop,*pop_lab,*pop_button,*box,*pop_play;
    pop=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_usize(GTK_WIDGET(pop),250,250);
    pop_lab=gtk_label_new(" ");
    char status[100];
    strcpy(status,"Game over! Final score : ");
    char score_arr[5];
    sprintf (score_arr, "%d", (int) score);
    strcat(status,score_arr);
    gtk_label_set(GTK_LABEL(pop_lab),&status);
    pop_button=gtk_button_new_with_label("Exit!");
    pop_play=gtk_button_new_with_label("Play Again!");
    g_signal_connect(G_OBJECT(pop_button),"clicked",gtk_main_quit,NULL);
    g_signal_connect(G_OBJECT(pop_play),"clicked",restart,pop);
    box=gtk_vbox_new(TRUE,3);
    gtk_box_pack_start (GTK_BOX (box),pop_lab, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (box), pop_play, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (box), pop_button, FALSE, FALSE, 5);
    gtk_container_add (GTK_CONTAINER (pop), box);
    gtk_widget_show_all(pop);
}



int main( int   argc,
          char *argv[] )
{
    /* GtkWidget is the storage type for widgets */
    GtkWidget *button;
    gtk_init (&argc, &argv);

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    fixed = gtk_fixed_new ();
    gtk_window_set_title (GTK_WINDOW (window), "Doncey Kong");


    gtk_signal_connect (GTK_OBJECT (window), "destroy",
                        GTK_SIGNAL_FUNC (gtk_exit), NULL);

    gtk_signal_connect (GTK_OBJECT (window), "delete_event",
                        GTK_SIGNAL_FUNC (gtk_exit), NULL);


    gtk_widget_realize(window);

    label=gtk_label_new("SCORE : 0");
    gtk_widget_show(label);
    bckgrnd_wid= xpm_create(window, "/home/karina/CLionProjects/untitled/background.png");
    gtk_widget_set_usize(GTK_WIDGET(bckgrnd_wid),1000,600);
    gtk_widget_show(bckgrnd_wid);
    gtk_fixed_put (GTK_FIXED (fixed), bckgrnd_wid, 0, 0);

    gtk_widget_set_usize(GTK_WIDGET(label),100,100);
    gtk_fixed_put (GTK_FIXED (fixed), label, 20, 20);

    //Mario
    mario_wid= xpm_create(window, "/home/karina/CLionProjects/untitled/mario.png");
    gtk_widget_show(mario_wid);
    gtk_fixed_put (GTK_FIXED (fixed), mario_wid, x_pos, 500);

    //DK
    donkey= xpm_create(window, "/home/karina/CLionProjects/untitled/imgs/donkeykong1_2.png");
    gtk_widget_show(donkey);
    gtk_fixed_put (GTK_FIXED (fixed), donkey, 10, 10);

    //Barril normal
    barrel_normal= xpm_create(window, "/home/karina/CLionProjects/untitled/imgs/cask(1).png");
    gtk_widget_show(barrel_normal);
    gtk_fixed_put (GTK_FIXED (fixed), barrel_normal, x_cord, y_cord);

    //Barril freefall
    barrel_freefall= xpm_create(window, "/home/karina/CLionProjects/untitled/imgs/cask(1).png");
    gtk_widget_show(barrel_freefall);
    gtk_fixed_put (GTK_FIXED (fixed), barrel_freefall, x_cord_free, y_cord_free);

    g_signal_connect(G_OBJECT(button), "key_press_event", G_CALLBACK(key_press_cb), mario_wid);
    timer = gtk_timeout_add (10, move_barrel_normal, barrel_normal);
    gtk_timeout_add (10, move_barrel_freefall, barrel_freefall);
/* Pack and show all our widgets */
    gtk_widget_show(fixed);
    gtk_container_add (GTK_CONTAINER (window), fixed);
    gtk_widget_set_usize(GTK_WIDGET(window),1000,600);
    gtk_widget_show (window);

    /* Rest in gtk_main and wait for the fun to begin! */
    gtk_main ();

    return(0);
}