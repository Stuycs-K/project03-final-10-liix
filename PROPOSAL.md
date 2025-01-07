# Final Project Proposal

## Group Members:

Irvin Li
       
# Intentions:

The goal of this project is to design and implement a system in C where multiple client processes can send file contents to a server. The server will sort these content into a central document, which remains accessible only by the server. Semaphores will be used to prevent any congestion that may happen during file transmission and uploading.
    
# Intended usage:

The system is designed for centralized file management. Clients interact with the system via a command-line interface. Their workflow includes:
 - Running a client program to specify and send a file's content in bytes to the server.
 - Receiving feedback on the success or failure of the file transfer.
The server will handle incoming file content, sorting their contents, and add it to the main file. Clients cannot directly access this central document. Server will return the document when it is finished.

  
# Technical Details:

Allocating memory - Helps allocate enough memory to handle files and other parts of the project
Semaphores - Used to control the amount of clients that can be attended to and prevents conflict.
File Handling - Used to process files and write into the main file found in the server.
Pipes- Using named and unnamed pipes to communicate between server and client.

    
# Intended pacing:

January 10: Finish the pipe portion of the project and ensure that clients can communicate with the server. (Bare minimum)
January 13: Get semaphores and permissions complete
January 17: Have the file and sorting aspect of the project complete (Project should be basically finished)
January 21: Have project complete along with video
