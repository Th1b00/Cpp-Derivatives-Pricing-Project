
<div align="center">

# C++ Derivatives Pricing Project

### ESILV · Financial Engineering · 2026

**Implementation of financial derivatives pricing models using C++ and object-oriented programming.**

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Visual Studio](https://img.shields.io/badge/Visual_Studio_2022-5C2D91?style=for-the-badge&logo=visualstudio&logoColor=white)
![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)

![Status](https://img.shields.io/badge/Status-In_Development-orange?style=flat-square)
![Academic Project](https://img.shields.io/badge/Academic_Project-ESILV-blue?style=flat-square)

</div>

---

## 📖 About the Project

This project is developed as part of the **C++ for Finance** course at **ESILV — École Supérieure d'Ingénieurs Léonard de Vinci**, during the fourth year of the Financial Engineering program.

The objective is to design and implement financial derivatives pricing models in C++, combining **financial mathematics, numerical methods, and object-oriented programming**.

The project covers analytical pricing, binomial tree methods, Monte Carlo simulations, and early exercise features.

---

## 🚀 Project Modules

The project is organized into four main parts:

| Module | Model | Description |
|:---:|---|---|
| **I** | Black-Scholes | European Call & Put pricing and Delta calculation |
| **II** | Cox-Ross-Rubinstein | Binomial tree pricing of European vanilla and digital options |
| **III** | Monte Carlo | Stochastic simulation, Asian options and confidence intervals |
| **IV** | American Options | Early exercise optimization and Black-Scholes approximation |

### Project Architecture

```mermaid
flowchart TD
    A["C++ Derivatives Pricing"]
    A --> B["I. Black-Scholes"]
    A --> C["II. CRR Binomial Tree"]
    A --> D["III. Monte Carlo"]
    A --> E["IV. American Options"]

    B --> F["European Options"]
    C --> G["Vanilla & Digital Options"]
    D --> H["European & Asian Options"]
    E --> I["Early Exercise"]

    style A fill:#1e3a5f,color:#fff,stroke:#1e3a5f
    style B fill:#2563eb,color:#fff,stroke:#2563eb
    style C fill:#2563eb,color:#fff,stroke:#2563eb
    style D fill:#2563eb,color:#fff,stroke:#2563eb
    style E fill:#2563eb,color:#fff,stroke:#2563eb
```

---

## 🛠️ Technologies & Concepts

**Development Environment**

- C++
- Microsoft Visual Studio 2022
- Git & GitHub

**Programming Concepts**

- Object-Oriented Programming (OOP)
- Inheritance & Polymorphism
- Abstract Classes & Virtual Functions
- Operator Overloading
- Templates & STL
- Random Number Generation

**Financial Models**

- Black-Scholes Model
- Cox-Ross-Rubinstein Binomial Model
- Monte Carlo Simulation
- Risk-Neutral Valuation

---

## 👥 Team Members

| Name | Institution | Major |
|---|---|---|
| **Thibault Michel** | ESILV | Financial Engineering |
| **Yanis Messas** | ESILV | Financial Engineering |
| **Nassim Slaouti** | ESILV | Financial Engineering |
| **Khelil Mehiri** | ESILV | Financial Engineering |

---

<div align="center">

**ESILV — Financial Engineering · Academic Year 2026–2027**

*Developed as part of the C++ for Finance course.*

</div>
