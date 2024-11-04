# Docker Notes

## Installation and Basics

- `yum install docker -y`: Install Docker
- `service docker status`: Check the status of the Docker service
- `docker info`: Display system-wide information about Docker
- `service docker start`: Start the Docker service
- `docker images`: List all Docker images
- `docker ps`: List all running Docker containers
- `docker ps -a`: List all running and stopped Docker containers

## Running Containers

- `docker run -it <container> /bin/bash`: Run a container interactively with a Bash shell
- `docker pull <container>`: Pull a Docker image from a registry
- `docker search <term>`: Search for Docker images

## Container Management

- `docker run -it --name <name> ubuntu /bin/bash`: Run a container with a custom name
- `docker start <docker name>`: Start a stopped container
- `docker attach <docker name>`: Attach to a running container
- `docker rm <name>`: Delete a container
- `docker diff <container>`: Show changes made to a container's filesystem

## Building Images

- `docker commit <container> <imagename>`: Create a new image from a container's changes
- `Dockerfile`: Instructions for building a Docker image
- `docker build -t <name> .`: Build a Docker image from a Dockerfile

## Volumes and Networking

- `VOLUME ["/myvolume"]`: Declare a volume in a Dockerfile
- `docker run -it --name <name> --privileged=true --volumes-from <which container volume to share> <ubuntu> /bin/bash`: Share a volume between containers
- `docker run -it --name hostcont -v /home/ec2-user:/aalu --privileged=true ubuntu /bin/bash`: Map a host directory to a container

## Port Exposure

- `docker run -td --name <name> -p 80:80 ubuntu`: Expose a container's port to the host

## Docker Hub

- `docker login`: Log in to Docker Hub
- `docker tag image1 aalupakoda/project1`: Tag a local image for Docker Hub
- `docker push aalupakoda/project1`: Push an image to Docker Hub
- `docker pull <name>`: Pull an image from Docker Hub

## Cleanup

- `docker stop $(docker ps -a -q)`: Stop all containers
- `docker rm $(docker ps -a -q)`: Delete all stopped containers
- `docker rmi -f $(docker images -q)`: Delete all images

## Database Example

- `docker run --name mysql-container -e MYSQL_ROOT_PASSWORD=root -e MYSQL_DATABASE=testdb -p 3306:3306 -d mysql:latest`: Run a MySQL container