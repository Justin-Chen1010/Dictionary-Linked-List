# Extracting Lists to create Dictionaries for Searching

**Version 1.0.0**

Create a simple dictionary via a linked list to store information from the Melbourne Census Land Use and Employment. The user of this program should be able to use this dictionary to retrieve information about businesses in Melbourne using the business name, as they would if it was a dictionary. 

## How you would call the program:
```
dict datafile outputfile < keyfile
```
We can insert the keys that we want to find for example "Tim Hortons, Starbucks".
Then the program will call the functions to query the database and return any dictionary matches

## Example Output:

```
StarBucks−−>Census year:  2018 || Block ID: 1101 || Property ID: 108973 || Baseproperty ID: 108973 || CLUE small area:  Docklands || Industry (ANZSIC4) code:  4511 || Industry (ANZSIC4)description:  Cafes and Restaurants || x coordinate:  144.95223 || y coordinate:  -37.81761 || Location:(-37.81761044, 144.9522269) ||

```

Extension of the program with KD-Trees: https://github.com/Justin-Chen1010/kd-tree
