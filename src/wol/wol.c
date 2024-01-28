#include <stdlib.h>

#include "wol.h"

uint8_t* get_magic_packet(machine* machine, uint8_t* packet){
    for (int i = 0; i < 6; i++)
    {
        packet[i] = UINT8_MAX;
    }
    for (int i = 6; i < MAGIC_PACKET_BYTES; i++)
    {
        packet[i] = machine->mac_address[i % 6];
    }
    return packet;
}

machine_stack** create_machine_stack(machine_stack** stack){
    (*stack) = malloc(sizeof(machine_stack));
    (*stack)->value = NULL;
    (*stack)->next_machine = NULL;
    return stack;
}


machine_stack* push_to_machine_stack(machine_stack* stack, machine* value){
    if(stack->value == NULL){
        stack->value=value;
        return stack;
        // stack = malloc(sizeof(machine_stack));
        // stack->value = value;
        // stack->next_machine = NULL;
        // return stack;
    }
    machine_stack* node = stack;
    while (node->next_machine != NULL)
    {
        node = node->next_machine;
    }
    machine_stack* new_node = malloc(sizeof(machine_stack));
    new_node->value = value;
    new_node->next_machine = NULL;

    node->next_machine = new_node;
    return stack;
}

machine* pop_machine_stack(machine_stack** stack){
    machine_stack* previous_val = *stack;
    machine_stack* current_val = *stack;
    if(current_val == NULL){
        return NULL;
    }
    while(current_val->next_machine != NULL){
        previous_val = current_val;
        current_val = current_val->next_machine;
    }
    previous_val->next_machine = NULL;

    machine* new_machine = malloc(sizeof(machine));
    *new_machine = *current_val->value;

    // only 1 value in the stack
    if(previous_val == current_val){
        stack = NULL;
    }

    free(current_val);
    return new_machine;
}

void clear_machine_stack(machine_stack** stack){
    if(stack == NULL){
        return;
    }
    while(stack != NULL){
      pop_machine_stack(stack);
    }
}

uint8_t get_machine_stack_size(machine_stack* stack){
    if(stack == NULL){
        return NULL;
    }
    uint8_t stack_size = 1;
    while(stack->next_machine != NULL){
        stack_size++;
        stack = stack->next_machine;
    }
    return stack_size;
}

machine* get_machine_at_index(machine_stack* stack, uint8_t index){
    if(stack == NULL){
        return NULL;
    }
    uint8_t stack_size = 0;
    while(stack_size != index){
        if(stack->next_machine == NULL){
            return NULL;
        }
        stack = stack->next_machine;
        stack_size++;
    }
    return stack->value;
}