# UHL

**UHL** - unreal helper library, toolset to help developers working with AI, GAS, customizing editor and so on.
Goal is to became a tool that insta-installed on new project creation.
All tools are mostly tested on melee combat so if you have other background and think that something should
work another way or have an idea on how to improve developer experience feel free to [discuss](https://github.com/Ciberusps/unreal-helper-library/discussions).

Support: `UE5.4 - UE5.6`

TODO: screeshot from FAB

## ✨ Features

- Utils - utility functions for your game, e.g. `GetProjectVersion`, `GetAssetsOfClass`, `GetHighestPoint`
- Editor - editor customization, e.g. `Custom thumnails`, `Custom class icon`

## 🚀 Install & ⬆️ Update

### From source (recommended)

```bash
// install as git submodule to your plugins folder
git submodule add https://github.com/Ciberusps/UHL.git ./Plugins/UHL

// to update plugin
git submodule update --remote`
```

### From marketplace

for now not listed

## 🧩 Modules

UHL consists of 3 modules:

- **UnrealHelperLibrary** - Blueprint Function Libraries. Most functionality can be tested in `Gyms`(maps for testing atomic/single gameplay mechanic), all `Gyms` located in `/Plugins/UnrealHelperLibrary/Content/Gyms`
- **UnrealHelperEditor** - optional module with editor customization, e.g. custom thumnails, custom class icons
- **UHL Utils (EditorUtilityWidget)** - widget with tools helping you make trivial things, like `ConvertToORM` quite often task when you want to combine 3 textures `Occlusion`, `Roughness`, `Metalic` in one ORM texture

## 📄 Documentation

**[📚 UnrealHelperLibrary](#unrealhelperlibrarybpl)**

> - [UnrealHelperLibraryBPL](#unrealhelperlibrarybpl)
>   - Gameplay
>     - GetActorClosestToCenterOfScreen
>     - GetMostDistantActor
>    <!--  - CreateGenericGASGameplayEffectSpec -->
>   - RelativeAngles
>     - [RelativeAngleToActor](#relativeangletoactor)
>     - [GetPointAtRelativeAngle](#getpointatrelativeangle)
>     - [GetPointAtRelativeDirection](#getpointatrelativedirection)
>     - [GetPointAtAngleRelativeToOtherActor](#getpointatanglerelativetootheractor)
>     - [GetPointAtDirectionRelativeToOtherActor](#getpointatdirectionrelativetootheractor)
>     - [DirectionToAngle](#directiontoangle)
>   - UI/Screen
>     - GetViewportSizeUnscaled
>   - Misc
>     - [GetProjectVersion](#getprojectversion)
>     - [GetNamesOfComponentsOnObject](#getnamesofcomponentsonobject)
>     - [GetAssetsOfClass](#getassetsofclass)
>     - GetBuildType
>    <!--  - GetActorComponentByName -->
>    <!--  - GetSceneComponentByName -->
>   - Debug
>     - DrawDebugLineOnCanvas
>   - Other
>     - [GetHighestPoint](#gethighestpoint)
> - [LoadingUtilLibrary](#loadingutillibrary)
>   - [ApplyDefaultPriorityLoading](#applydefaultpriorityloading)
>   - [ApplyStreamingPriorityLoading](#applystreamingpriorityloading)
>   - [ApplyHighestPriorityLoading](#applyhighestpriorityloading)
>   - [ApplyCustomPriorityLoading](#applycustompriorityloading)
>   - [ForceGarbageCollection](#forcegarbagecollection)
>   - [FlushLevelStreaming](#flushlevelstreaming)
> - [TraceUtilsBPL](#traceutilsbpl)
>   - SweepCapsuleSingleByChannel
> - [Settings](#settings)
>   - [UHL Settings](#uhl-settings)
> - [Subsystems](#subsystems)
>   - [UHLHUD](#uhlhud)
> - AnimNotifyState (ANS)
>   - [ANS_UHL_Base](#ans_uhl_base)
>   - [ANS_ActivateAbility](#ans_activateability)

**[⌨ Editor](#-uhl-editor)**

> - [Custom thumnails](#custom-thumnails)
> - [Custom class icon](#custom-class-icon)
> - [UHL Utils (Editor Utility Widget)](#uhl-utils-editor-utility-widget)
>   - [ConvertToORM](#converttoorm)

### UnrealHelperLibraryBPL

#### > RelativeAngles

#### `RelativeAngleToActor`

for most cases you want to use "InRange" like `IsOtherActorInAngle` (or `IsOtherCharacterInRange` if you want to check distance)

![image](https://github.com/Ciberusps/unreal-helper-library/assets/14001879/4a695df4-9583-451c-801b-98e63c8ad5c8)

#### `GetPointAtRelativeAngle`

![image](https://github.com/Ciberusps/unreal-helper-library/assets/14001879/4c2f5e47-9f5c-4e70-8d77-57cb7383290a)
![image](https://github.com/Ciberusps/unreal-helper-library/assets/14001879/c0026be0-ce3a-4ee5-84e6-b8e90474fdb9)

#### `GetPointAtRelativeDirection`

![image](https://github.com/Ciberusps/unreal-helper-library/assets/14001879/c1ea6dda-4ccf-4441-a7d0-dc83ac977a9c)
![image](https://github.com/Ciberusps/unreal-helper-library/assets/14001879/a33a93ad-f470-4dec-8c2c-6c76b275207f)

#### `GetPointAtAngleRelativeToOtherActor`

#### `GetPointAtDirectionRelativeToOtherActor`

#### `DirectionToAngle`

#### > Misc

#### `GetProjectVersion`

Get project version from "Project Settings"

![image](https://github.com/Ciberusps/unreal-helper-library/assets/14001879/c15d4c68-48d2-4d49-bee6-438f18064f9f)

![image](https://github.com/Ciberusps/unreal-helper-library/assets/14001879/d9e7e53c-b0ba-47cc-b63a-099423a89346)

#### `GetNamesOfComponentsOnObject`

Get names of actor components on object, usefull for [`GetOptions` UPROPERTY](https://benui.ca/unreal/uproperty/#getoptions)

#### `GetAssetsOfClass`

#### > Other

#### `GetHighestPoint`

#### `ANS_UHL_Base`

**ANS_UHL_Base** - base `AnimNotifyState` class with commonly used features like

- subscribing `OnMontageBlendingOut` by overriding `OnMontageBlendingOut` can be disabled by `bUseOnMontageBlendingOut=false(true by default)`
- more come later

### Subsystems

#### UHLHUD

HUD with debugging abilities, for now used to display debug bars(e.g. HP/hidden attributes)

### 🔃 LoadingUtilLibrary

**UHLLoadingUtilLibrary** - loading utils from Lyra

#### ApplyDefaultPriorityLoading

#### ApplyStreamingPriorityLoading

#### ApplyHighestPriorityLoading

#### ApplyCustomPriorityLoading

#### ForceGarbageCollection

#### FlushLevelStreaming

### 🎯 TraceUtilsBPL

**UHLTraceUtilsBPL** - trace utils

### ⌨ UHL Editor

**UHL Editor** - optional module with editor customization, e.g. custom thumnails, custom class icons

#### `Custom thumnails`

![image](https://github.com/user-attachments/assets/c24fd8bb-0ffe-4666-afd5-8800df650c35)

**Custom thumnails** - to override thumbnail by your own, just implement `IUHLEditorCustomThumbnail` interface and define your own icon using `GetCustomThumbnailIcon()`

> [!WARNING]
> ⚠️ NOT sure that blueprints supported for now

```C++
// UInventoryItem.h
#if WITH_EDITOR
#include "UHLEditorCustomThumbnail.h"
#endif

// IUHLEditorCustomThumbnail not available in production build
#if !WITH_EDITOR
class IUHLEditorCustomThumbnail {};
#endif

class GAMECODE_API UInventoryItem : public UObject,
    public IUHLEditorCustomThumbnail
{
/** IUHLEditorCustomThumbnail **/
#if WITH_EDITOR
    virtual UTexture2D* GetCustomThumbnailIcon_Implementation() const override;
#endif
/** ~IUHLEditorCustomThumbnail **/
}

------------------------------------------------------------------

// UInventoryItem.cpp
#if WITH_EDITOR
UTexture2D* UInventoryItem::GetCustomThumbnailIcon_Implementation()
{
    return Description.Icon;
}
#endif
```

Thanks to [this post](https://forums.unrealengine.com/t/custom-thumbnail-not-display-asset-is-never-loaded/143155/2?u=ciberus) and [this](https://forums.unrealengine.com/t/custom-thumbnail-on-blueprint/337532/3?u=ciberus)

#### `Custom class icon`

**Custom class icon** - to override classes icons on your own, just set settings in `Project Settings -> Editor -> UnrealHelperEditor Settings`

![image](https://github.com/user-attachments/assets/da940018-2120-4b81-84da-5237e97e9c86)

[List of default Unreal Engine Editor icons](https://github.com/EpicKiwi/unreal-engine-editor-icons)

Thanks to [this post](https://www.quodsoler.com/blog/customize-your-unreal-class-icons) and [this](https://forums.unrealengine.com/t/how-to-load-a-font-uasset-and-use-it-for-fslatefontinfo/1548466/3?u=ciberus)

### UHL Utils (Editor Utility Widget)

⚒️ InProgress

### ConvertToORM

Combines separate `Occlusion`, `Roughness`, `Metalic` textures into one `ORM`

TODO check ref - https://github.com/Atulin/ChannelMerger

## Special Thanks

[@Ingarnm](https://github.com/Ingarnm), [@Vamp1rk0](https://github.com/Vamp1rk0) for feedback
