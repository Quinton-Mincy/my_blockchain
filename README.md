# Welcome to My Blockchain
***

## Task
Create a blockchain that is modified and saved through command line prompts.

## Description
When the program is running, a prompt is provided to show the user the number of nodes in the blockchain, "[sN]>", where N is the number of nodes. The commands available
to the user are listed below in the Usage section. The blockchain nodes, blocks and the quantity of each are 

## Installation
With the project files installed, just run the 'make' and 'make clean' commands.

## Usage
Then execute the program by typing "./my_blockchain filname" into the command prompt, where filename
is the name of an existing blockchain text file, or a new file. During the runtime of the program, the user will enter a number of valid commands such as:
    -add node 
    -remove node 
    -add block 
    -remove block 
    -ls 
    -sync 
    -quit
All these commands, except ls, sync and quit, take in a single argument. For the add node and remove node commands, they take a single integer value (an existing node id) as their argument,
The add/remove block takes in a string as their argument (an existing block id). The ls, sync and quit commands do not take in any arguments, however ls can take an option (-l). The ls command prints
all of the current nodes on the chain, and the -l flag includes the blockchain (if any) that exists on a given node. The sync command synchronizes all of the nodes to the genesis node's (the first node created) blockchain,
so all nodes have an identical copy of the blockchain. The quit command exits the blockchain, and then the user is prompted ([y/n]) on whether or not they want to save the modifications they made to the blockchain.

## How It Works
Below is a screenshot of a creation of a new blockchain.

![Screen Shot 2022-12-01 at 3 14 24 PM](https://user-images.githubusercontent.com/73136662/205150610-b513921d-d9a3-4941-9778-8dbd7bc75393.png)

As you can see, commands such as add node, add block, and sync are used to create the blockchain. After exiting the program, and saving it, you can see that the nodes, blocks and their number are saved to the file
(new_blockchain) that the user designated when starting the program.

Taking a look at what the blockchain looks like before sync is called:

![Screen Shot 2022-12-01 at 3 21 57 PM](https://user-images.githubusercontent.com/73136662/205151852-5d54d63e-1ab1-40fb-9b63-f514840dd24c.png)

we can see that the blocks were only added to the first node, the genesis node. This node is especially important, as it verifies whether or not the user is attempting to add a node or a block that already exists.
The sync command then copies the valid blockchain that the genesis node has to the other nodes on the chain.

Rolling the blockchain we just created back up, we will explore the other commands that are at the users disposal.

![Screen Shot 2022-12-01 at 3 34 44 PM](https://user-images.githubusercontent.com/73136662/205154057-25217d36-2fa8-4b26-82b6-aaafa0c6c948.png)

We can see by printing the existing blockchain, the file that was created before was parsed through and reverted back to its linked list form (including the node and block counts). Again we see that adding a block only takes
effect in the genesis node until the blockchain is synchronized. The 2 commands 'remove node' and 'remove block' are also showcased here, note that when a block is removed, the chain is automatically synchronized, as their should not exist a
block on any node on the chain that does not exist on the genesis node. We also show here that if the user attempts to use the remove node function on the genesis node, they will be denied. 

## Moving Forward
A few improvements that would benefit this application, besides a GUI perhaps, are as follows. Firstly, a more robust character set that the user can use, namely special characters such as '@' and '.' so emails can easily be added to the 
blockchain. Furthering the idea of an email list, adding some sort of verification service to the program as to ensure that users attempting to join the blockchain meet some sort of criteria would be a and interesting feature. In this example,
a more complex authentication system would be in order (perhaps consulting more than just the genesis node for verication). Another major fix that can be implemented immediatley is to load the nodes (structs) of the linked list directly to the 
desired file. Instead of extracting the nids and bids (node and block ID's) from them and creating a text, csv-like, file, parsing the file would be done much more cleanly. Lastly, it would be helpful to the user to be able to add multiple nodes and blocks in a single command. Currently, only one node/block can be added at a time.

### The Core Team
* [Quinton MINCY](//github.com/Quinton-Mincy) - Developer

<span><i>Made at <a href='https://qwasar.io'>Qwasar Silicon Valley</a></i></span>
<span><img alt='Qwasar Silicon Valley Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
