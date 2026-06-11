## Overview

The project follows a structured class design:

ACharacter  
└── COABaseCharacter  
  └── COAAvatar  

- **COABaseCharacter**: Handles shared logic (health, healing, walk speed)
- **COAAvatar**: Handles player input, camera, running, and stamina system

## Features

- Third person movement and camera
- Sprint system with stamina drain and recovery
- Stamina lockout when depleted

## Controls

- **W / A / S / D** → Move  
- **Mouse** → Look  
- **Space** → Jump  
- **Left Shift** → Run  

## Stamina System

- Starts at **MaxStamina (100)**
- Drains while moving
- Regenerates when idle
- At **0 stamina**:
- Running is disabled (`bStaminaDrained = true`)
- Running is re-enabled only after full recovery

## Notes

- Built with **Unreal Engine 5.6**
- Uses both **C++ and Blueprint systems**
- `.gitignore` excludes generated Unreal folders