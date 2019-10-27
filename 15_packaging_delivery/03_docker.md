
# Docker - Containerization technology

## What is Docker?[^what_is_docker]

* Docker is a tool designed to make it easier to create, deploy, and run applications by using containers
* Containers allow a developer to package up an application with all of the parts it needs, such as libraries and other dependencies, and ship it all out as one package
* Docker is a bit like a virtual machine. But unlike a virtual machine, rather than creating a whole virtual operating system, Docker allows applications to use the same
  Linux kernel as the system that they're running on and only requires applications be shipped with things not already running on the host computer. This gives a significant
  performance boost and reduces the size of the application.

## Docker command

* docker build - builds a Docker image from a Dockerfile
* docker push - pushes the Docker image to a central registry
* docker run - download image, create and run container (image instance)

## Dockerfile example

Acts as the definition of a runnable container 

```
FROM python:3

ADD my_script.py /

RUN pip install pystrich

CMD [ "python", "./my_script.py" ]
```

[^what_is_docker]: [What is Docker?](https://opensource.com/resources/what-docker)

\newpage