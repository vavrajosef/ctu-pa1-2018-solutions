  #include<stdio.h>
#include<stdlib.h>

const int FEES_SIZE = 26;
const char A = 'A';
const char Z = 'Z';
typedef struct NODE
{
  int start;
  int end;
  double price;
  struct NODE *next;
} node;

int load_fees(node**);
void free_fees(node**);
int load_and_compute_requests(node**);
int assign_new_part(node**, int, int, char, double, int);
double calculate_total_price(node**, int, int);
void print_prices(node**, int, int);

int main()
{
  node *fees[FEES_SIZE] = {NULL};
  printf("Zmeny:\n");
  if(!load_fees(fees))
  {
    printf("Nespravny vstup.\n");
    free_fees(fees);
    return 1;
  }
  printf("Hledani:\n");
  if(!load_and_compute_requests(fees))
  {
    printf("Nespravny vstup.\n");
    free_fees(fees);
    return 1;
  }
  free_fees(fees);
  return 0;
}

int load_fees(node **fees)
{
  char temp_char, temp_label;
  int start, end, load_result, priority = 0;
  double price;
  if(scanf(" %c", &temp_char) != 1 || temp_char != '{')
  {
    return 0;
  }
  do {
    load_result = scanf(" [ %d - %d : %c = %lf ] %c", &start, &end, &temp_label, &price, &temp_char);
    if(load_result != 5 || start < 0 || start >= end || price < 0 || temp_label < A || temp_label > Z)
    {
      return 0;
    }
    int result = assign_new_part(fees, start, end, temp_label, price, priority);
    if(result != 1)
    {
      return result;
    }
    priority++;
  } while(temp_char == ',');
  if(temp_char != '}')
  {
    return 0;
  }
  return 1;
}

void free_fees(node **fees)
{
  for(int i = 0; i < FEES_SIZE; i ++)
  {
    node* head = fees[i];
    while(head!= NULL)
    {
      node* tmp = head;
      head = head->next;
      free(tmp);
    }
  }
}

int load_and_compute_requests(node **fees)
{
  int start, end, load_result;
  while(1)
  {
    load_result = scanf(" %d %d", &start, &end);
    if(load_result == EOF)
    {
      return 1;
    }
    if(load_result != 2 || start == end || start < 0 || end < 0)
    {
      return 0;
    }
    print_prices(fees, start, end);
  }
}

int assign_new_part(node **fees, int start, int end, char temp_label, double price, int priority)
{
  node *new_part = (node *)malloc(sizeof(*new_part));
  if(new_part == NULL)
  {
    return 0;
  }
  new_part->start = start;
  new_part->end = end;
  new_part->price = price;
  new_part->next = NULL;
  node* before = NULL;
  node *head = fees[temp_label - A];

  while(head != NULL)
  {
    if(start < head->end)
    {
      break;
    }
    before = head;
    head = head->next;
  }
  if(head == NULL)
  {
    if(before == NULL)
    {
      fees[temp_label - A] = new_part;
    } else
    {
      before->next = new_part;
    }
  }

  while(head!=NULL)
  {
    if(start > head->start && end >= head->end)
    {
      head->end = start;
      new_part->next = head->next;
      head->next = new_part;
      before = head;
      head = new_part;
    } else
    if(start <= head->start && end < head->end && end > head->start)
    {
      if(before == NULL)
      {
        fees[temp_label - A] = new_part;
      } else
      {
        before->next = new_part;
      }
      new_part->next = head;
      head->start = end;
      break;
    } else
    if(start > head->start && end < head->end)
    {
      node *old_part_fragment = (node *)malloc(sizeof(*old_part_fragment));
      if(old_part_fragment == NULL)
      {
        return 0;
      }
      old_part_fragment->price = head->price;
      old_part_fragment->next = head->next;
      old_part_fragment->start = end;
      old_part_fragment->end = head->end;
      head->end = start;
      head->next = new_part;
      new_part->next = old_part_fragment;
      break;
    } else
    if(start <= head->start && end >= head->end)
    {
      if(before == NULL)
      {
        fees[temp_label - A] = new_part;
      } else
      {
        before->next = new_part;
      }
      new_part->next = head->next;
      free(head);
      head = new_part;
    } else
    if(end <= head->start)
    {
      if(before == NULL)
      {
        fees[temp_label - A] = new_part;
      } else
      {
        before->next = new_part;
      }
      new_part->next = head;
      break;
    }
    head = head->next;
  }

double calculate_total_price(node * fee, int smaller, int greater)
{
  double result = 0;
  while(fee != NULL)
  {
    int current_end = fee->end;
    int current_start = fee->start;
    if(current_start > greater)
    {
      break;
    }
    if(current_start <= greater && current_end >= smaller)
    {
        int priced_part_start = current_start > smaller ? current_start : smaller;
        int priced_part_end = current_end < greater ? current_end : greater;
        result += fee->price * (priced_part_end - priced_part_start);
        //printf("\n%lf = %lf * (%d - %d)\n", result, fee->price, priced_part_end, priced_part_start);
    }
    fee=fee->next;
  }
  return result;
}

void print_prices(node **fees, int start, int end)
{
  printf("%d - %d:", start, end);
  int greater = start > end ? start : end;
  int smaller = start < end ? start : end;
  int multiple_prices = 0;
  for(int i = 0 ; i < FEES_SIZE ; i ++)
  {
      if(fees[i] != NULL)
      {
        double total_price = calculate_total_price(fees[i], smaller, greater);
        if(total_price != 0)
        {
          if(multiple_prices == 0)
          {
            multiple_prices = 1;
          } else
          {
            printf(",");
          }
          printf(" %c=%lf", A + i, total_price);
        }
      }
  }
  printf("\n");
}
