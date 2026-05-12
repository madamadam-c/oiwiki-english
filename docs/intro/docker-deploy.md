This page introduces how to deploy an **OI Wiki** environment with Docker.

???+ warning "Warning"
    The following steps must be executed as the root user or as a user in the docker group.

## Pull the **OI Wiki** Image

```bash
# Run one of the following commands on the host
# Docker Hub image (official image repository)
docker pull 24oi/oi-wiki
# DaoCloud Hub image (mainland China image repository)
docker pull daocloud.io/sirius/oi-wiki
# Tencent Hub image (mainland China image repository)
docker pull ccr.ccs.tencentyun.com/oi-wiki/oi-wiki
```

## Build the Image Yourself

```bash
# Run the following commands on the host
# Clone the Git repository
git clone https://github.com/OI-wiki/OI-wiki.git
cd OI-wiki/
# Build the image
docker build -t [name][:tag] . --build-arg [variable1]=[value1] [variable2]=[value2]...
```

-   Required: set `[name]` as the image name. Optional: set `[tag]` as the image tag. If a tag is set, the runtime image name consists of both parts.
-   You can set environment variables with the `--build-arg` parameter.

Available environment variables:

-   Set `WIKI_REPO` to use a mirror of the Wiki repository. If unset, GitHub is used automatically.
-   Set `PYPI_MIRROR` to use a PyPI repository mirror. If unset, the official PyPI is used automatically.
    -   In mainland China, the TUNA mirror `https://pypi.tuna.tsinghua.edu.cn/simple/` is recommended.
-   Set `LISTEN_IP` to change the listening IP. If unset, it defaults to `0.0.0.0`, which listens on all IP addresses.
-   Set `LISTEN_PORT` to change the listening port. If unset, it defaults to `8000`.

Example:

```bash
docker build -t OI_Wiki . --build-arg WIKI_REPO=https://hub.fastgit.xyz/OI-wiki/OI-wiki.git PYPI_MIRROR=https://pypi.tuna.tsinghua.edu.cn/simple/
# Build an image named OI_Wiki with the default tag, use FastGit to accelerate cloning, and use the TUNA mirror.
```

## Run the Container

```bash
# Run the following command on the host
docker run -d -it [image]
```

-   Required: set `[image]` to specify the image. For example, the image pulled from Docker Hub is `24oi/oi-wiki`; the one pulled from DaoCloud Hub is `daocloud.io/sirius/oi-wiki`.
-   Required: set `-p [port]:8000` to map the container port to a host port. If this option is omitted, no port is exposed by default. Replace `[port]` with the host port. After setting it, you can access **OI Wiki** on the host at `http://127.0.0.1:[port]`.
-   Set `--name [name]` to set the container name. It is empty by default. Replace `[name]` with your custom container name. To view the container id, run `docker ps`.

## Use the Container

???+ note "Note"
    The examples are based on an Ubuntu latest deployment.

Enter the container:

```bash
# Run the following command on the host
docker exec -it [name] /bin/bash
```

If you remove `-d` when running the container above, you can enter the container's bash shell directly; after exiting, the container stops. With `-d`, it runs in the background and must be stopped manually. The command above for entering the container applies to the `-d` method.

Special commands:

```bash
# Run the following commands inside the container
# Update the git repository
wiki-upd

# Use our custom theme
wiki-theme

# Build mkdocs; static pages will be generated under the site directory
wiki-bld

# Build mkdocs and render MathJax; static pages will be generated under the site directory
wiki-bld-math

# Run a server. Visit http://127.0.0.1:8000 inside the container or http://127.0.0.1:[port] on the host to preview the result
wiki-svr

# Fix Markdown
wiki-o
```

Exit the container:

```bash
# Run the following command inside the container
# Exit
exit
```

## Stop the Container

```bash
# Run the following command on the host
docker stop [name]
```

## Start the Container

```bash
# Run the following command on the host
docker start [name]
```

## Restart the Container

```bash
# Run the following command on the host
docker restart [name]
```

## Remove the Container

```bash
# Run the following command on the host
# Stop the container before removing it
docker rm [name]
```

## Update the Image

Just run `pull` again. Usually, it will not update.

## Remove the Image

```bash
# Run the following command on the host
# Remove containers built from the oi-wiki image before removing the image
docker rmi [image]
```

## Questions

If you have questions, feel free to open an [issue](https://github.com/OI-wiki/OI-wiki/issues/new/choose)!
