Environnement
======================
Android

======================

Environnement

Windows, Mac, Linux

IDE 

Eclipse, IntelliJ, NetBeans, etc ..

======================
iOS

======================
Environnement

Mac

IDE 

XCode

======================
Windows

======================

Environnement

Windows Phone SDK 8.0 requires 64-bit Windows 8 Pro or higher.

Emulator :

System requirements

In the BIOS, the following features must be supported:
Hardware-assisted virtualization.
Second Level Address Translation (SLAT).
Hardware-based Data Execution Prevention (DEP).
4 GB or more of RAM.
64-bit version of Windows 8 Pro edition or higher.

Network requirements

DHCP.
Automatically configured DNS and gateway settings.

Hyper-V requirements

In the BIOS, the following features must be enabled:
Hardware-assisted virtualization.
Second Level Address Translation (SLAT).
Hardware-based Data Execution Prevention (DEP).
In Windows, Hyper-V must be enabled and running.
You have to be a member of the local Hyper-V Administrators group.

System requirements

Your computer must meet the following requirements:

BIOS

In the BIOS, the following features must be supported:
Hardware-assisted virtualization.
Second Level Address Translation (SLAT).
Hardware-based Data Execution Prevention (DEP).

RAM

4 GB or more.

Operating system

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


IDE

Visual Studio 2013.

======================
BlackBerry

======================

Environnement

Mac

IDE 

XCode
