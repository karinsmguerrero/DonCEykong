#include<stdio.h>
#include<string.h>
#include <gtk/gtk.h>
GtkWidget *fixed,*window;
GtkWidget *bckgrnd_wid,*archr_wid,*arrow_wid,*balloon_wid,*burst_wid;

GtkWidget *label;
int timer;


int score=0;

//*************************
GtkWidget *mario_wid, *donkey, *barrel_normal, *barrel_freefall, *barrel_mix, *life1, *life2, *life3, *fire;
GtkWidget *l1,*l2,*l3;
int x_pos=0;
int y_pos=500;
int x_aux=0;
int y_aux=500;
int mario_tag=0;
int speed = 10;
int lives = 3;

int x_cord = 105;
int y_cord = 55;

int x_cord_free = 105;
int y_cord_free = 55;

int forward = 0;
int forward_free = 0;

int fire_x = 105;
int fire_y = 550;

int start_fire = 0;

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
int fire_inginition(GtkWidget *data){

    if(x_cord > 1000)
    {
        start_fire = 1;
    }

    if(start_fire == 1){
        gtk_fixed_put (GTK_FIXED (fixed), fire , fire_x, fire_y);
        fire_x += 5;
    }
}

int move_barrel_normal(GtkWidget *data)
{
    if((y_pos == 500 && y_cord == 525 || y_pos == 335 && y_cord == 365 ||  y_pos == 185 && y_cord < 205 || y_pos == 20 && y_cord == 54) && abs(x_cord - x_pos) == 1){
        switch (lives){
            case 3:
                lives = 2;
                gtk_widget_destroy(life1);
                break;
            case 2:
                lives = 1;
                gtk_widget_destroy(life2);
                break;
            case 1:
                lives = 0;
                gtk_widget_destroy(life3);
                game_over();
                break;
        }
    }

    if(x_cord > 1000)
    {
        forward = 0;
        y_cord = 55;
        x_cord = 105;

        gtk_fixed_put (GTK_FIXED (fixed), barrel_normal , x_cord, y_cord);
    }

    if(forward == 0){
        if(x_cord > 870 && 54 < y_cord && y_cord < 215 ){
            if(205 < y_cord && y_cord < 215)
                forward = 1;
            y_cord += 5;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_normal, x_cord, y_cord);
        }
        else if(x_cord > 870 && 335 < y_cord && y_cord < 530 ){
            if(525 < y_cord && y_cord < 530)
                forward = 1;
            y_cord += 5;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_normal, x_cord, y_cord);
        }
        else {
            x_cord += 5;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_normal, x_cord, y_cord);
        }
        return TRUE;
    } //backward
    else{
        if(x_cord < 100 && 209 < y_cord && y_cord < 380 ){
            if(365 < y_cord && y_cord < 380)
                forward = 0;
            y_cord += 5;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_normal, x_cord, y_cord);
        }
        else {
            x_cord -= 5;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_normal, x_cord, y_cord);
        }
        return TRUE;
    }


}


int move_barrel_freefall(GtkWidget *data)
{
    if(x_cord_free < 2)
    {
        forward_free = 0;
        y_cord_free = 55;
        x_cord_free = 105;

        gtk_fixed_put (GTK_FIXED (fixed), barrel_freefall , x_cord_free, y_cord_free);
    }

    if(forward_free == 0){
        if(x_cord_free > 870 && 54 < y_cord_free && y_cord_free < 215 ){
            if(205 < y_cord_free && y_cord_free < 215)
                forward_free = 1;
            y_cord_free += 5;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_freefall, x_cord_free, y_cord_free);
        }
        else if(x_cord_free > 870 && 380 < y_cord_free && y_cord_free < 530 ){
            if(528 < y_cord_free && y_cord_free < 530)
                forward_free = 1;
            y_cord_free += 5;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_freefall, x_cord_free, y_cord_free);
        }
        else {
            x_cord_free += 5;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_freefall, x_cord_free, y_cord_free);
        }
        return TRUE;
    } //backward
    else{
        if(x_cord_free < 300 && 185 < y_cord_free && y_cord_free < 530 ){
            if(528 < y_cord_free && y_cord_free < 530)
                forward_free = 0;
            y_cord_free += 5;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_freefall, x_cord_free, y_cord_free);
        }
        else {
            x_cord_free -= 5;
            gtk_fixed_move(GTK_FIXED (fixed), barrel_freefall, x_cord_free, y_cord_free);
        }
        return TRUE;
    }

}

int move_mario_start(GtkWidget *data)
{
   gtk_fixed_move (GTK_FIXED (fixed), data , x_pos, y_pos);
   return FALSE;
}

int move_mario_jumpd(GtkWidget *data)
{
  if(x_aux==y_pos){
    return FALSE;
  }
  x_aux+=5;
  gtk_fixed_move (GTK_FIXED (fixed), data , x_pos, x_aux);
  return TRUE;
}

int move_mario_jumpu(GtkWidget *data)
{
  if(y_aux==(y_pos-45)){
    x_aux=y_aux;
    mario_tag = gtk_timeout_add (speed, move_mario_jumpd, data);
    return FALSE;
    //return FALSE;
  }
   y_aux-=5;
   gtk_fixed_move (GTK_FIXED (fixed), data , x_pos, y_aux);
   g_message("%s, %d","JUUUUMP: ",y_aux);
   return TRUE;
}
int move_mario_right(GtkWidget *data)
{
   x_pos+=15;
   gtk_fixed_move (GTK_FIXED (fixed), data , x_pos, y_pos);
   g_message("%s, %d","XPOS: ",x_pos);
   g_message("%s, %d","YPOS: ",y_pos);
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
            if(y_pos==500||(y_pos==185&&x_pos<=900&&x_pos>=105)
            ||(y_pos==20&&x_pos<=825&&x_pos>=15)||(y_pos==335&&x_pos<=825&&x_pos>=15)){
              mario_tag = gtk_timeout_add (speed, move_mario_right, data);
            }
          }
        }
        if(kevent->keyval==65361){
          g_message("%s","LEFT");
          if(x_pos>=0){
            if(y_pos==500||(y_pos==185&&x_pos<=915&&x_pos>=120)
            ||(y_pos==20&&x_pos<=840&&x_pos>=30)||(y_pos==335&&x_pos<=840&&x_pos>=30)){
              mario_tag = gtk_timeout_add (speed, move_mario_left, data);
            }
          }
        }
        if(kevent->keyval==65364){
          g_message("%s","DOWN");
          if((x_pos==705&&y_pos<500&&y_pos>=335)||(x_pos==390&&y_pos<335&&y_pos>=185)
          ||(x_pos==300&&y_pos>=335&&y_pos<=410)||(x_pos==180&&y_pos<=320&&y_pos>=185)
          ||(x_pos==465&&y_pos<=170&&y_pos>=20)||(x_pos==705&&y_pos<=170&&y_pos>=20)
          ||(x_pos==270&&y_pos<=170&&y_pos>=25)){
            mario_tag = gtk_timeout_add (speed, move_mario_down, data);
          }
        }
        if(kevent->keyval==65362){
          g_message("%s","UP");
          //Escaleras
          if((x_pos==705&&y_pos>335)||(x_pos==390&&y_pos<=335&&y_pos>=200)
          ||(x_pos==300&&y_pos>=350&&y_pos<=425)||(x_pos==180&&y_pos<=335&&y_pos>=200)
          ||(x_pos==465&&y_pos<=185&&y_pos>=35)||(x_pos==705&&y_pos<=185&&y_pos>=35)
          ||(x_pos==195&&y_pos<=20&&y_pos>=-55)||(x_pos==270&&y_pos<=185&&y_pos>=40)){
            mario_tag = gtk_timeout_add (speed, move_mario_up, data);
          }if(x_pos==195&&y_pos<=-60&&y_pos>=-80){
            x_pos=0;
            y_pos=500;
            speed+=5;
            score++;
            g_message("%s, %d","SCORE: ",score);
            set_score();
            mario_tag = gtk_timeout_add (speed, move_mario_start, data);
          }
        }
        if(kevent->keyval==32){
          g_message("%s","SPACE");
          y_aux=y_pos;
          mario_tag = gtk_timeout_add (speed, move_mario_jumpu, data);
          gtk_fixed_move (GTK_FIXED (fixed), data , x_pos, y_pos);
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
y_pos=500;

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
    //int timer;
    gtk_init (&argc, &argv);

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    fixed = gtk_fixed_new ();
    gtk_window_set_title (GTK_WINDOW (window), "DonCE Kong");


    gtk_signal_connect (GTK_OBJECT (window), "destroy",
                        GTK_SIGNAL_FUNC (gtk_exit), NULL);

    gtk_signal_connect (GTK_OBJECT (window), "delete_event",
                        GTK_SIGNAL_FUNC (gtk_exit), NULL);


    gtk_widget_realize(window);
    button = gtk_button_new_with_label("SHOOT!");
    label=gtk_label_new("SCORE : 0");
    gtk_widget_show(label);
    bckgrnd_wid= xpm_create(window, "/home/karina/CLionProjects/untitled/background.png");
    gtk_widget_set_usize(GTK_WIDGET(bckgrnd_wid),1000,600);
    gtk_widget_show(bckgrnd_wid);
    gtk_fixed_put (GTK_FIXED (fixed), button, 200, 200);
    gtk_fixed_put (GTK_FIXED (fixed), bckgrnd_wid, 0, 0);
    gtk_widget_show(button);
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

    //Vidas
    life1 = xpm_create(window, "/home/karina/CLionProjects/untitled/imgs/life_white.png");
    gtk_widget_show(life1);
    gtk_fixed_put (GTK_FIXED (fixed), life1, 850, 20);

    life2 = xpm_create(window, "/home/karina/CLionProjects/untitled/imgs/life_white.png");
    gtk_widget_show(life2);
    gtk_fixed_put (GTK_FIXED (fixed), life2, 900, 20);

    life3 = xpm_create(window, "/home/karina/CLionProjects/untitled/imgs/life_white.png");
    gtk_widget_show(life3);
    gtk_fixed_put (GTK_FIXED (fixed), life3, 950, 20);

    //fuego
    fire = xpm_create(window, "/home/karina/CLionProjects/untitled/imgs/fire.png");
    gtk_widget_show(fire);

    //************************

    g_signal_connect(G_OBJECT(button), "key_press_event", G_CALLBACK(key_press_cb), mario_wid);

    //Barriles automáticos
    gtk_timeout_add (10, move_barrel_normal, barrel_normal);
    gtk_timeout_add (10, move_barrel_freefall, barrel_freefall);

    //fuego
    gtk_timeout_add (20, fire_inginition, fire);

/* Pack and show all our widgets */
    gtk_widget_show(fixed);
    gtk_container_add (GTK_CONTAINER (window), fixed);
    gtk_widget_set_usize(GTK_WIDGET(window),1000,600);
    gtk_widget_show (window);

    /* Rest in gtk_main and wait for the fun to begin! */
    gtk_main ();

    return(0);
}
