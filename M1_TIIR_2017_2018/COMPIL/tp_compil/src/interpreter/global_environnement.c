#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter/global_environnement.h"

struct environnement_s * add_to_list(struct environnement_s * list,struct environnement_s * new_elem){
  if(list == NULL){
    list = new_elem;
    return list;
  }else{
    struct environnement_s * tmp = list;
    while(tmp->next != NULL)
      tmp = tmp->next;
    tmp->next = new_elem;
    new_elem->prev = tmp;
    return list;
  }
}

struct environnement_s * init_maillon(char * id,struct value_s * value){

    struct environnement_s * new_maillon = (struct environnement_s *)malloc(sizeof(struct environnement_s));
    if(new_maillon == NULL){
      return NULL;
    }
    strcpy(new_maillon->id,id);
    new_maillon->value = value;
    new_maillon->next = NULL;
    new_maillon->prev = NULL;
    return new_maillon;
}

int contains_key(char * id, struct environnement_s * env){
  struct environnement_s * tmp = env;
  while(tmp != NULL){
    if(strcmp(id,tmp->id) == 0){
      return 1;
    }
    tmp = tmp->next;
  }
  return 0;
}

struct environnement_s * get_maillon (char * id,struct environnement_s * env){
  struct environnement_s * tmp = env;
  while(tmp != NULL){
    if(strcmp(id,tmp->id) == 0){
      return tmp;
    }
    tmp = tmp->next;
  }
  return NULL;
}

struct environnement_s * put(char * id,struct value_s * value,struct environnement_s * env){
  if(contains_key(id,env)){
    //L'id existe déjà, on édite le maillon éxistant
    struct environnement_s * maillon = get_maillon(id,env);
    struct value_s * old_value = maillon->value;
    maillon->value = value;
    //if(old_value != NULL)
    //  free(old_value);
    return env;

  }else{
    //L'id n'éxiste pas, on créer un maillon et on l'ajoute
    struct environnement_s * new_maillon = init_maillon(id,value);
    return add_to_list(env,new_maillon);
  }
}

struct value_s * get(char * id, struct environnement_s * env){
  struct environnement_s * tmp = env;
  while(tmp != NULL){
    if(strcmp(id,tmp->id) == 0){
      return tmp->value;
    }
    tmp = tmp->next;
  }
  return NULL;
}
