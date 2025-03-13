#include <superkarel.h>

void turn_right(){
   set_step_delay(0);
   turn_left();
   turn_left();
   turn_left();
   set_step_delay(150);
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

void face_to_east(){
      while(not_facing_east()){
         turn_left();
      }
}

void pick_all_beepers(){
   while(true){
      if(front_is_clear()){
         step();
         if(beepers_present()) pick_beeper();
      }
      else if(front_is_blocked() && beepers_in_bag()){
         vzad();
         break;
      }
      else if(front_is_blocked() && no_beepers_in_bag() && no_beepers_present()){
         vzad();
         break;
      }
   }
}

void putting_system_first_line(){
   while(true){
      if(front_is_clear()){
         if(right_is_blocked() && no_beepers_present()){
            if(beepers_in_bag()) put_beeper();
            step();
         }
         else if(left_is_blocked()){
            if(beepers_present()) pick_beeper();
            else step();
         }
         else step();
      }
      else if(front_is_blocked() && no_beepers_in_bag()){
         turn_left();
         step();
         turn_left();
         break;
      }
   }
}

void sorting_system(){
   pick_all_beepers();
   while(true){
   if(front_is_clear()){
         turn_right();
         step();
         if(beepers_present()){
            vzad();
            step();
            if(beepers_in_bag()) put_beeper();
            turn_right();
         }
         else{
            vzad();
            step();
            turn_right();
         }
      step();
   }
   else{
      turn_left();
      if(front_is_blocked() && right_is_blocked()){
         vzad();
         while_front_is_clear();
         break;
      }
      else{
         step();
         turn_left();
      }
      break;
   }
   }
}
bool search_start(){
   while(front_is_clear() && right_is_clear()){
      step();
   }
   if(front_is_blocked() && right_is_clear()){
      vzad();
      while_front_is_clear();
      turn_left();
      step();
      turn_left();
      return false;
   }
   else if(front_is_blocked() && right_is_blocked()){
      vzad();
      while(left_is_blocked()){
         step();
      }
      turn_left();
      step();
      turn_right();
      while_front_is_clear();
      vzad();
      return true;
   }
   else if(front_is_clear() && right_is_blocked()){
      vzad();
      while(left_is_blocked()){
         step();
      }
      turn_left();
      step();
      turn_right();
      while_front_is_clear();
      vzad();
      return true;
   }
   return false;
}

int main(){
   turn_on("task_3.kw");
   set_step_delay(50);
   face_to_east();
   pick_all_beepers();
   putting_system_first_line();
   while(true){
      sorting_system();
      if(front_is_blocked()){
         break;
      }
      if(left_is_blocked() && front_is_blocked()) break;
   }
   turn_right();
   while(true){
      if(search_start()){
         turn_off();
         break;
      }
   }
}
