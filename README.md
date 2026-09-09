# 🤖 Explorer-M1 ("Bobi") — Advanced Custom Quadruped & Landmine Detection Robot

![GitHub release (latest by date)](https://img.shields.io/github/v/release/ZanMujicic/Explorer-M1?color=blue&style=for-the-badge)
![17th Festival Rada Winner](https://img.shields.io/badge/Award-1st_Place_Festival_Rada_Travnik_2026-gold?style=for-the-badge)
![ESP32](https://img.shields.io/badge/Microcontroller-ESP32--WROOM--32-red?style=for-the-badge&logo=espressif)
![ESP-NOW Protocol](https://img.shields.io/badge/Protocol-ESP--NOW--2.4GHz-brightgreen?style=for-the-badge)
![Fabrication](https://img.shields.io/badge/Fabrication-3D_Print_%2B_Laser_Cut-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

---

## 📌 O Projektu / About The Project

**Explorer-M1 (od milja prozvan "Bobi")** je napredni četveronožni (quadrupedal) robot dizajniran za inspekciju nepristupačnih terena i detekciju minsko-eksplozivnih sredstava. Robot kombinuje **hibridnu mehaničku konstrukciju** (laserski sječena šperploča + 3D printani nosači i zglobovi), **custom PCB/wire harness**, te distributivnu kontrolu pokreta preko **ESP32** mikrokontrolera i **PCA9685** PWM drivera.

Projekt je osvojio **1. mjesto na 17. Festivalu rada srednjih техниčki i stručnih škola Bosne i Hercegovine** u Travniku (maj 2026. godine).

---

## 📸 Galerija Slika (Image Gallery)

### 🤖 Robot (Explorer-M1 / Bobi)
|<img src="media/1000115369.jpg" width="400">|<img src="media/1000062379.jpg" width="400">|
|:---:|:---:|
| **Frontalni prikaz na terenu (prijem / terenski uslovi)** | **Prikaz na stolu sa uključenim upravljačem** |

|<img src="media/1000041235.jpg" width="400">|<img src="media/1000041129.jpg" width="400">|
|:---:|:---:|
| **Bliži profil robota (stranična perspektiva)** | **Prikaz elektronike, hladnjaka i osvjetljenja** |

---

### 📐 CAD / Dizajn & Izrada
|<img src="media/1000041198.jpg" width="800">|
|:---:|
| **Rastavljeni 3D / CAD model komponenata šasije i leg-linkage mehaničkog sistema** |

---

### 🎮 Bežični Upravljač (Custom Remote Controller)
|<img src="media/1000055893.jpg" width="400">|<img src="media/1000055892.jpg" width="400">|
|:---:|:---:|
| **Upravljač sa ESP32, džojstikom i custom tasterima** | **Upravljač sa montiranim 3D printanim držačem telefona/ekrana** |

---

## 🎥 Video Demonstracije

Zbog prirode prikaza na GitHub-u, priloženi snimci se nalaze u direktoriju `media/`:

* 📹 **[`media/1000062387.mp4`](media/1000062387.mp4)** — *Demonstracija hoda robota i kretanja na travi / neravnom terenu.*
* 📹 **[`media/1000061814.mp4`](media/1000061814.mp4)** — *Prikaz rada upravljača i instantnog odziva komandi preko ESP-NOW.*
* 📹 **[`media/1000041223.mp4`](media/1000041223.mp4)** — *Testiranje zglobova, FPV kamere, servo servisa i LED osvjetljenja.*

---

## ⚙️ Tehnička Arhitektura & Komponente

### 🧠 Elektronika & Senzori
* **Glavni Kontroler:** ESP32 Development Board (Dual-core 240MHz, Wi-Fi & Bluetooth LE)
* **Servo Controller:** PCA9685 16-channel 12-bit I2C PWM Driver
* **Servomotori:** 8x / 12x High-Torque **MG996R** metal-gear servomotori
* **IMU Senzor:** **MPU6050** (3-osni žiroskop + 3-osni akcelerometar) za stabilizaciju i kalibraciju nagiba
* **Senzor Detekcije:** Custom induktivni/metal-detection modul sa zvučnom i vizuelnom signalizacijom
* **Video & Kamera:** FPV Micro Camera sa ugrađenim prednjim LED farom za noćno izviđanje
* **Napajanje & Hlađenje:** 
  * High-current Li-ion / LiPo baterijski paket
  * **XL4015** Buck DC-DC step-down konvertor podesivog napona/struje
  * Aktivno hlađenje sa dedicated fan-om i aluminijskim hladnjacima na naponskoj sekciji

### 🕹️ Custom Remote Controller (Daljinski Upravljač)
* **Protokol:** **ESP-NOW** (Peer-to-peer 2.4GHz protokolarne poruke sa latencijom < 10ms)
* **Ulazi:** 2-osni analogni džojstik, 5x taktilnih dugmadi za promjenu brzine/režima hoda
* **Šasija:** Ergonomsko 3D printano kućište sa laserski sječenom gornjom pločom i držačem za pametni telefon / FPV monitor

---

## 🏆 Postignuća i Takmičenja

* 🥇 **1. Mjesto** — *17. Festival rada srednjih tehničkih i stručnih škola BiH* (Travnik, 2026.)
* 🚀 **Izlaganje** — *Sci&Tech Challenge 2026* & *Maker Faire Sarajevo*

---

## 👨‍💻 Autor

**Žan Mujičić**
* 🏫 JU Mješovita srednja industrijska škola Zenica, Bosna i Hercegovina
* 🤝 Saradnja: **INPUT Centar Zenica**
* 📧 Kontakt: *ZanMujicic (GitHub)*
