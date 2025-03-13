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

void forward_znachka(){
   set_step_delay(0);
   while(true){
      if(left_is_clear()){
         turn_left();
         step();
         put_beeper();
         vzad();
         step();
         turn_left();
      }
      step();
      if (front_is_blocked()) break;
   }
   set_step_delay(50);
}

bool all_blocked(){
   if(front_is_blocked() && left_is_blocked() && right_is_blocked())return true;
   else return false;
}

bool cheking(){
   while(true){
      if(right_is_clear()){
         turn_right();
         step();
      }
      else if(front_is_clear()) step();
      else if(left_is_clear()){
         turn_left();
         step();
      }
      else{
         vzad();
         step();
      }
      if(no_beepers_present()) continue;
      if(beepers_present()){
         step();
         if(beepers_present()) return true;
      }
      vzad();
      step();

      if(facing_east()){
         if(front_is_clear()) step();
         else if(left_is_clear()){
            turn_left();
            step();
         } else{
            vzad();
            step();
         }
      }
      return false;
   }
}

void search_sklad(){
   if(left_is_blocked()) return;

   put_beeper();
   turn_left();
   step();

   if(all_blocked()){
      pick_beeper();
      vzad();
      step();
      pick_beeper();
      turn_left();
      return;
   }

   if(cheking()){
      pick_beeper();
      vzad();
      step();
      pick_beeper();
      vzad();
   }else if(cheking()){
      pick_beeper();
      vzad();
      step();
      vzad();
   }else if(cheking()){
      pick_beeper();
      vzad();
      step();
      vzad();
   }else if(cheking()){
      pick_beeper();
      vzad();
      step();
      vzad();
   }else if(cheking()){
      pick_beeper();
      vzad();
      step();
      vzad();
   }
   step();
   turn_left();
}

int main() {
   turn_on("task_7.kw");
   set_step_delay(50);

   forward_znachka();
   if(front_is_blocked() && left_is_clear()){
      turn_left();
      step();
      put_beeper();
      vzad();
      step();
      turn_left();
   }
   vzad();
   while_front_is_clear();
   vzad();

   while(true){
      search_sklad();
      step();
      if(front_is_blocked()) break;
   }
   search_sklad();


   turn_off();
}
