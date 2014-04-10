Environnement
======================

Android
----------------------

* __Environnement__

Windows, Mac, Linux

* __IDE__

Eclipse, IntelliJ, NetBeans, etc ..


iOS
----------------------

* __Environnement__

Mac

* __IDE__ 

XCode


Windows
----------------------

* __Environnement__

Windows Phone SDK 8.0 requires 64-bit Windows 8 Pro or higher.

__Emulator :__

_System requirements_

In the BIOS, the following features must be supported:

Hardware-assisted virtualization.

Second Level Address Translation (SLAT).

Hardware-based Data Execution Prevention (DEP).

4 GB or more of RAM.

64-bit version of Windows 8 Pro edition or higher.

_Network requirements_

DHCP.

Automatically configured DNS and gateway settings.

_Hyper-V requirements_

In the BIOS, the following features must be enabled:

Hardware-assisted virtualization.

Second Level Address Translation (SLAT).

Hardware-based Data Execution Prevention (DEP).

In Windows, Hyper-V must be enabled and running.

You have to be a member of the local Hyper-V Administrators group.

__System requirements :__

Your computer must meet the following requirements:

_BIOS_

In the BIOS, the following features must be supported:

Hardware-assisted virtualization.

Second Level Address Translation (SLAT).

Hardware-based Data Execution Prevention (DEP).

_RAM_

4 GB or more.

_Operating system_

Windows 8

64-bit

Pro edition or higher


Add in your vmx to enable Hyper-V

hypervisor.cpuid.v0 = "FALSE"

mce.enable = "TRUE"

since your system now access 

Activer ou désactiver des fonctionnalités Windows

Activer Hyper-V, Outils d'aministration Hyper-V et Plateforme Hyper-V

Si vous n'arriver pas à activerla plateforme il vous faudra :

Aller dans le centre de maintenance que vous trouverez dans le panneau de configuration est positionner au minimum (Ne jamais m'avertir).

Puis activer le LUAEnable de la regedit pour se faire aller dans la regedit :

HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\system

et mettez la valeur à 0

Puis depuis une commande administrator

bcdedit /set hypervisorlaunchtype Off --> pour pouvoir annuler le lancement de l'hypervisor au démarrage et ainsi le modifier depuis le panneau de configuration.


* __IDE__

Visual Studio 2013.


BlackBerry
----------------------

* __Environnement__


* __IDE__ 

