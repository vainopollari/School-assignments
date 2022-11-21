const http = require('http');
const path = require('path');
const fs = require('fs');

http.createServer((request, response) => {
    if (request.url === '/classical') {
        readFileSendResponse('homer.html', 'application/html', response);
    } 
    else if (request.url === '/dystopy') {
        readFileSendResponse('bradbury.html', 'application/html', response);
    } 
    else if (request.url === '/') {
        readFileSendResponse('index.html', 'application/html', response);
    } 
    else {
      response.statusCode = 404;
      response.statusMessage = 'Requested content not found';
      response.end();
    }
  }).listen(3000)

const readFileSendResponse = (fileName, contentType, response) => {
    fs.readFile(path.resolve(fileName), function(error, file) {
      if (error) {
        response.writeHead(404);
        response.write('An error occured: ', error);
      } else {
        response.writeHead(200, { 'Content-Type': contentType });
        response.write(file);
      }
      response.end();
    })
  }