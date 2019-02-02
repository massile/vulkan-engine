# Vulkan 3D Engine

## Vocabulary

- **Physical device** : A physical Vulkan-capable hardware device (GPU). It represents a unique device.
- **Device** : Refers to a logical representation of the physical device in an application.
- **Host**: Refers to a representation of the CPU and its associated memory.
- **Queue**  : An interface between the execution engine and the application. Gathers the jobs and dispatches them to the physical device.
- **Command** : An instruction to do some act.
- **Command buffer** :  A collection of commands; it records the commands and submits them to the queues.


## Vulkan's execution model

Command buffers are submitted into queues, which are consumed by the physical device to be processed.
![](executionModel.png)

Synchronizarion between queues can be controlled using:

 - **Semaphores** : Synchronizes work across multiple queues.
 - **Events** : Synchronizes work within a command buffer / within command buffers submitted to a queue.
 - **Fences** : Allows synchronization between the host (CPU) and the device (GPU).
 - **Pipeline barriers** : An instruction which ensures that commands are executed in order.

 
## The object model

All Vulkan entities are recognized using [handles](https://stackoverflow.com/a/13023487)

 - **Dispatchable handles** : Opaque types. Data can only be accessed using API routines.
 - **Non-Dispatchable handles** : May contain the object information, rather than a pointer to the structure.

## The object lifecycle's syntax

Within Vulkan :
 - **Create syntax** : Created using the vkCreate\* command which takes a Vk\*CreateInfo as a parameter.
 - **Destroy syntax** : Destroyed using vkDestroy\*.

Within an object [pool](https://en.wikipedia.org/wiki/Pool_(computer_science)) or [heap](https://stackoverflow.com/a/80113):
 - **Allocate syntax** : Created using the vkAllocate\* command which takes a Vk\*AllocateInfo as a parameter.
 - **Freeing syntax** : Released from the pool / memory using vkFree\*.


## Components of a Vulkan application

![](vulkanApp.png)

 - **Driver** : Acts as an interface between the application and the device itself.
 - **Application** : A user program that is intended to make use of Vulkan.
 - **WSI** : Set of extensions for the unification of the presentation layer accross different platforms.
 - **SPIR-V**: Precompiled binary format for specifying shaders.
 - **LunarG SDK**:  Set of tools and resources to aid Vulkan application development (docs, debug tools, ...).


## The Vulkan programming model

![](programmingModel.png)

### Hardware initialization

The application activates the Vulkan drivers by communicating with the *loader* its responsibilites are:
  - **locating the driver**
  - **it should be platform independent** (platform differences are expressed as *extensions*)
  - **layers can be injected** (driver doesn't need to determine whether the API is used correctly anymore)

## Window presentation surfaces

We need an image to perform the drawing task and put it on the presentation window to display it.

![](windowPresentation.png)

Context creation does not need to involve the window system (unlike OpenGL), it is managed through WSI:
It manages the ownership of images via a **swapchain**: while one image is displayed, other ones can be prepared.

![](swapchain.png)

Steps in the application:
  - **Create a native window**
  - **Attach a WSI surface to the window**
  - **Create the swapchain to present to the surface**
  - **Request the images from the swapchain**

## Resource setup

Unlike OpenGL, Vulkan provides full low-level and explicit control of the memory.
Memory heaps' performance:
  - **Host local**: Slower
  - **Device local**: Faster

Memory type configurations:
  - **Device local**: 
     + physically attached to the physical device
     + visible to the *device*
     + not visible to the *host*
  - **Device local, host visible**
:gi t    + physically attached to the physical device
     + visible to the *device*
     + visible to the *host*
  - **Host local, host visible**: 
     + local memory of the host
     + visible to the *device*
     + visible to the *host*

