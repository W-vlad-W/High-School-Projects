#include <superkarel.h>

void turn_right(){
   set_step_delay(0);
   turn_left();
   turn_left();
   turn_left();
   set_step_delay(50);
}

void two_step(){
 step();
 step();
}

void while_front_is_clear(){
  while(front_is_clear()){
   step();
  }
}

void while_is_beeper(){
   while(beepers_present()){
      pick_beeper();
   }
}

void vzad(){
   turn_left();
   turn_left();
}

void face_to_south(){
      while(not_facing_south()){
         turn_left();
      }
}

void step_before_beeper(){
   while(true){
      step();
      if(beepers_present()) break;
   }
}


void putting_beepers(){
   if(no_beepers_present()) put_beeper();
   while_front_is_clear();
   if(no_beepers_present()) put_beeper();
   vzad();
   while(true){
      two_step();
      if(no_beepers_present()){
         vzad();
         step();
         put_beeper();
         vzad();
         step_before_beeper();
         vzad();
      }
      else if(beepers_present()){
         pick_beeper();
         vzad();
         step();
         put_beeper();
         step();
         pick_beeper();
         vzad();
         step_before_beeper();
         if(right_is_blocked()) turn_left();
         else if(left_is_blocked()) turn_right();
         break;
      }
   }
}

void checking(){
   while(true){
      if(front_is_blocked() && right_is_blocked()){
         turn_left();
         putting_beepers();
         break;
      }
      else if(front_is_blocked() && left_is_blocked()){
         turn_right();
         putting_beepers();
         break;
      }
      else if(front_is_blocked()){
         turn_left();
         while_front_is_clear();
      }
   }
}

void search_center(){
   while(true){
      step();
      turn_right();
      put_beeper();
      while_front_is_clear();
      if(beepers_present()){
         vzad();
         step_before_beeper();
         pick_beeper();
         turn_right();
      }
      else if(no_beepers_present()){
         vzad();
         step_before_beeper();
         pick_beeper();
         turn_right();
         step();
         put_beeper();
         break;
      }
   }
}

void doing_ram(){
   while(true){
      if(front_is_clear()) step();
      if(no_beepers_present()) put_beeper();
      if(front_is_blocked()){
         turn_left();
         break;
      }
   }
}

void scan(){
  step();
  turn_left();
  step();
  while(true){
      if(no_beepers_present()){
         step();
      }
      else if(beepers_present() && front_is_clear() && left_is_clear() &&
            right_is_clear()){
            vzad();
            if(front_is_clear()) break;
            else vzad();
      }
      else if(front_is_blocked()){
         vzad();
         while_front_is_clear();
         turn_left();
         step();
         turn_left();
         step();
      }
  }
}
bool if_tree_x_Y(){
   while(not_facing_west()){
      turn_left();
   }
   while_front_is_clear();
   turn_left();
   while_front_is_clear();
   vzad();
   two_step();
   if(front_is_blocked()) return true;
   else return false;
}

bool if_X_x_tree(){
   while(not_facing_south()){
      turn_left();
   }
   while_front_is_clear();
   turn_left();
   while_front_is_clear();
   vzad();
   two_step();
   if (front_is_blocked()) return true;
   else return false;
}

void func_1(){
   while_front_is_clear();
   turn_left();
   while_front_is_clear();
   doing_ram();
   doing_ram();
   doing_ram();
   doing_ram();
   doing_ram();
   step();
   turn_left();
   step();
}

void func_2(){
   checking();
   step();
   put_beeper();
   vzad();
   step();
   turn_left();
   doing_ram();
   doing_ram();
   doing_ram();
   doing_ram();
   doing_ram();
   scan();
}

void func_3(){
   checking();
   step();
   put_beeper();
   vzad();
   step();
   turn_left();
   doing_ram();
   doing_ram();
   doing_ram();
   doing_ram();
   doing_ram();
   scan();
}

int main(){
   turn_on("task_5.kw");
   set_step_delay(50);
   if(if_tree_x_Y() && if_X_x_tree()) func_1();
   else if(if_X_x_tree()) func_2();
   else if(if_tree_x_Y()) func_3();
   else{
      while_front_is_clear();

      checking();

      while_front_is_clear();

      checking();

      search_center();

      while_front_is_clear();
      turn_left();

      doing_ram();
      doing_ram();
      doing_ram();
      doing_ram();
      doing_ram();

      scan();
   }
   if(beepers_present()) pick_beeper();
   while(not_facing_north()) turn_left();
   turn_off();
}
