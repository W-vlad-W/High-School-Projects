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


void putting_beepers(){
   while_front_is_clear();
   vzad();
   while(true){
      if(no_beepers_present()){
         put_beeper();
         if(front_is_clear()) step();
      }
      else if(front_is_clear()) step();
      else if(front_is_blocked()){
         turn_left();
         if(front_is_clear()) step();
         break;
      }
   }
}

void restauration_column(){
   turn_left();
   while(true){
      if(beepers_present()){
         putting_beepers();
         break;
      }
      else if(front_is_clear()) step();
      else{
         vzad();
         while_front_is_clear();
         turn_left();
         step();
         break;
      }
   }
}


void last_column(){
   turn_left();
   while(true){
      if(beepers_present()){
         putting_beepers();
         break;
      }
      else if(front_is_clear()) step();
      else{
         vzad();
         while_front_is_clear();
         turn_left();
         break;
      }
   }
}


int main() {
   turn_on("task_4.kw");
   set_step_delay(50);

   while(true){
      restauration_column();
      if (front_is_blocked() && right_is_blocked()){
         last_column();
         break;
      }
   }
   turn_off();
}
