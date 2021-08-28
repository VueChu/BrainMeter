#include <Brain.h>
#include <Keyboard.h>

int MAX_NUM_PINS = 12, attentionValue;
/*
 * Author: VueChu
 * Github: https://github.com/VueChu/
 * I am using a doubly linked list because of how easily it can traverse throughout the list.
 * This is used as a way to display attention/focus values through a range of LEDs.
 * Where the first LED threshold value is 0.
 *  - Lower attention/focus values = Green LEDs will luminate. (Max Lower attention/focus range of values is 0-36)
 *  - Medium attention/focus values = Blue LED will luminate. (Medium attention/focus value is 45)
 *  - High attention/focus values = White LEDs will luminate. (High attention/focus range of values is 54-90).
 *  - Absolute attention/focus values = Red LEDs will luminate. (Max High attention/focus value is 99)
 */
 
class DoublyLinkedList
{  
private:
  struct Node
  {
    int pinNumber, value;
    Node* next;
    Node* prev;
  };
  Node* head;
  Node* tail;
  Node* currentNode;
  
public:
  DoublyLinkedList()
  {
    head = NULL;
    tail = NULL;
  }

  ~DoublyLinkedList()
  {
    Node* iterator = head;
    while(iterator)
    {
      Node* temp = iterator;
      iterator = iterator->next;
      delete temp;
    }
  }
  
  /*
   * setUpPins()
   * Will iterate through each node in the doubly linked list to retrieve its pin values to set it as an output.
   */
  void setUpPins()
  {
    Node* iterator;
    while(iterator) //While iterator is not NULL, assign the pins.
    {
      pinMode(iterator->pinNumber, OUTPUT);
    }
  }
  
  /*
   * insert()
   * Creates a node and inserts it into a doubly linked list. Each node will represent an LED on the breadboard.
   * params: int pinNumber, int value
   */
  void insert(int pinNumber, int value)
  {
    Node* temp = new Node();
    if(head == NULL && tail == NULL)  //If a doubly linked list is empty.
    {
      temp->pinNumber = pinNumber;
      temp->value = value;
      head = temp;
      tail = temp;
      currentNode = head;
    }
    else  //Insert at the end if a doubly linked list is not empty.
    {
      temp->pinNumber = pinNumber;
      temp->value = value;
      tail->next = temp;
      temp->prev = tail;
      tail = temp;
    }
  }

  /*
   * brainRun()
   * This function will iterate until the attention values are correctly displayed on the brain meter.
   * params: int attentionValue
   */
  void brainRun(int attentionValue)
  {
    bool exitWhileLoop = false, scanToggled = false;
    digitalWrite(currentNode->pinNumber, HIGH);
    while(!exitWhileLoop)
    {
      if(currentNode->next != NULL && attentionValue >= currentNode->next->value) //Increment condition
      {
      currentNode = currentNode->next;
      digitalWrite(currentNode->pinNumber, HIGH);
      }
      else if(currentNode->prev != NULL && attentionValue < currentNode->value) //Decrement condition
      {
        digitalWrite(currentNode->pinNumber, LOW);
        currentNode = currentNode->prev;
      }
      else  //No conditions above are satisfied, then exit the loop.
      {
        exitWhileLoop = true;
        Serial.println(attentionValue);
        Serial.print("Current node value: ");
        Serial.println(currentNode->value);
      }
    }
  }
};

DoublyLinkedList brainMeter;
Brain brain(Serial1);

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  setUpNodeAttributes();
  brainMeter.setUpPins();
}

void loop() 
{
  if(brain.update())
  {
    attentionValue = brain.readAttention();
    Serial.println(attentionValue);
    brainMeter.brainRun(attentionValue);
  }
}

/*
 * setUpNodeAttributes()
 * Creates a node's attributes with an assigned pin number, value for the attention threshold values, and inserts it to the doubly linked list.
 */
void setUpNodeAttributes()
{
  for(int i = 0; i < MAX_NUM_PINS; i++)
  {
    int pin = i + 2;
    int value = 9 * i;
    brainMeter.insert(pin, value);
  }
}
