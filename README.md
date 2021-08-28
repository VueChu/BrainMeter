# BrainMeter
A 12 LED display that would represent the user's focus/attention values using an Arduino Leonardo and the Arduino IDE.

# Author's Note:
I created this for the sole purpose of learning how to program on an Arduino, practicing object oriented programming and a doubly linked list.
This project was heavily inspired by Michael Reeves who used the Star Wars Force Trainer to drive his car with his mind. (insert link to video).
Thank you to kitschpatrol, rambo, and jospehfrazier for providing the library to parse data from the Neurosky EEG headsets and by providing a guide on how to physicallyt modify the Neurosky EEG chip. (insert link to github).
If you see anything that can be improved or have any tips (including this readme file), I would greatly appreciate any sort of feedback.

### Summary:
This program's purpose is to display the user's focus/attention values through a 12 LED display using the Mindflex EEG headset using an Arduino Leonardo on the Arduino IDE.


### Materials needed:
- Arduino Uno or any board that can utilize Serial - 1 (Click [here](https://www.arduino.cc/reference/en/language/functions/communication/serial/) to check which type of Serial you would have to use for this program.)
	- If you used a Leonardo like I did in the code BrainMeter.ino, you should be completely set with the Serial reference.
	- If you used an Uno, change the references "Serial1" to "Serial". This is due to the fact that Leonardo supports onboard USB, whereas the Uno does not.
- Breadboard - 1
- 150? resistors - 12
- LED - 12
- Any USB that is compatible with your Arduino that can be connected to a computer.
- A computer.

### Diagram:
![here]() <<Insert Link>>
### ---DoublyLinkedList Class---
- ### Struct Node
	- ```int pinNumber```
      - Pin will store the specified pin for each node.

	- ```int value```
		- Value will hold a threshold value for each node.

	- ```Node* next```
		- Will point to the memory address of the next node in the doubly linked list.
		
	- ```Node* prev```
		- Will point to the memory address of the previous node in the doubly linked list.
		
- ### Attributes
	- ```Node* head```
		- A pointer that keeps track of the first node in the doubly linked list.
		
	- ```Node* tail```
		- A pointer that keeps track of the last node in the doubly linked list.
		
	- ```Node* currentNode```
		- A pointer that keeps track of the current location of a node when traversing through the doubly linked list when given a attention/focus value of type int.
		
-	### CONSTRUCTOR
    - ```DoublyLinkedList(int pinNumber, int value)```
    
      - Instantiates the DoublyLinkedList class by taking in pinNumber and value.

- ### FUNCTIONS
  - ```void setUpPins()```
  
	  - Will iterate through each node in the doubly linked list to retrieve its pin values to set it as an output.

  - ```void insert(int pinNumber, int value)```

    - Creates a node and inserts it to the tail of the doubly linked list. Each node will represent an LED on the breadboard.
	- Params: int pinNumber, int value
	
  - ```void brainRun(int attentionValue)```
  
    - This function will iterate until the focus/attention values are correctly displayed on the brian meter.
	- Params: int attentionValue

### ---End of DoublyLinkedList Class---
### GLOBAL VARIABLES WORTH MENTIONING

- ```Brain brain(Serial1)```

  - brain is an object of type Brain that will utilize a Serial (dependent on which board you're using) object to allow communication with the arduino board and the headset. 
  
- ```DoublyLinkedList brainMeter```

  - brainMeter is an object of type DoublyLinkedList that will allow access, create, and modify the doubly linked list. 

### FUNCTIONS
- ```void setUpNodeAttributes()```

  - Creates a node's attributes with an assigned pin number, value for the attention threshold values, and inserts it to the doubly linked list.

