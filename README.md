[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Vh67aNdh)
File sorting

LiI - X

Irvin Li
       
### Project Description:

The goal of this project is to design and implement a system in C where multiple client processes can send files to a server. The server will sort these files into a central document, which remains accessible only by the server. Semaphores will be used to prevent any congestion that may happen during file transmission and uploading.
  
### Instructions:

run make client
Clients interact with the system via a command-line interface. Their workflow includes:
 - Running a client program to specify and send a file to the server.
 - Receiving feedback on the success or failure of the file transfer.
The server will handle incoming files, sorting their contents, and add it to the main file. Clients cannot directly access this central document. Server will return the document when it is finished.