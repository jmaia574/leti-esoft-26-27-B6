# Supplementary Specification (FURPS+)

**Project:** UK Labs Management System (UKLabsMS)  
**Course:** LETI-ESOFT 2026/2027  
**Team:** B6  
**Sprint:** 1

## 1. Introduction

This document specifies the supplementary functional and non-functional requirements of the UK Labs Management System (UKLabsMS), using the FURPS+ classification framework.

It complements the Use Case Diagram (UCD) and the Domain Model (DM) by capturing cross-cutting functional requirements, quality attributes, and architectural constraints.

Requirements are classified according to their origin:

- **Specified:** Explicitly stated in the Project Assignment.
- **Derived:** Inferred from the business processes and rules described in the Project Assignment.
- **Proposed:** Additional recommendations requiring stakeholder validation.

The term "shall" denotes a mandatory requirement, while "should" indicates a recommended enhancement.

## 2. Functionality

This section specifies functionality shared across multiple use cases, covering security, access control, traceability, and cross-cutting workflow rules.

| ID | Requirement | Origin |
|:---|:---|:---|
| FUN-01 | All system users (Staff Members and Clients) shall be authenticated before accessing the application. Authentication may be simulated during the prototype stage. | Specified |
| FUN-02 | The system shall prevent clients from accessing analysis results until the specialist doctor has prepared and validated the diagnostic report (`Report`). | Specified |
| FUN-03 | Following the completion of the diagnostic report by the specialist doctor, the system shall automatically notify the client via SMS and/or email that the results and report are available. | Specified |
| FUN-04 | The system shall support sorting clinical analysis results by the client's Tax Identification Number (`taxIdentificationNumber` / TIF) or by the client's name. | Specified |
| FUN-05 | The system shall maintain consistent associations across the complete analysis lifecycle: `Client`, `LabOrder`, `RegisteredTest`, `Sample`, `ChemicalAnalysis`, `ParameterResult`, and `Report`. | Derived |
| FUN-06 | The system should enforce role-based access control corresponding to the responsibilities of each `Staff Member` specialization (Administrator, Receptionist, Medical Lab Technician, Clinical Chemistry Technologist, Specialist Doctor) and `Client`. | Proposed |
| FUN-07 | The system should prevent clients from accessing another client's private clinical and personal information. | Proposed |
| FUN-08 | The system should maintain an audit trail of critical clinical operations, recording the responsible employee, operation type, and exact timestamp. | Proposed |

### 2.1 Security and Access Control

Clinical records are strictly confidential and must be protected against unauthorized disclosure or tampering.

The system distinguishes authentication from authorization:
- **Authentication:** Verifies the user's identity (simulated during the prototype stage).
- **Authorization:** Restricts system operations according to the user's role (enforcing the hierarchy defined for `Staff Member` actors).

### 2.2 Functional Traceability

- **FUN-01** maps to **UC01 (Authenticate User)**.
- **FUN-02** maps to **UC11 (Prepare Diagnostic Report)** and **UC12 (View Test Results and Report)**, enforcing Business Rule BR05.
- **FUN-03** maps to **UC11 (Prepare Diagnostic Report)** as an automated post-condition notification, enforcing Business Rule BR06.
- **FUN-04** maps to **UC12 (View Test Results and Report)**.
- **FUN-05** spans across the clinical workflow use cases: **UC06 (Register Client)**, **UC07 (Register Prescribed Test)**, **UC08 (Register Sample)**, **UC10 (Record Chemical Analysis Results)**, and **UC11 (Prepare Diagnostic Report)**.
- **FUN-06 to FUN-08** represent cross-cutting architectural constraints applicable to all operational use cases (**UC02 to UC12**).

## 3. Usability

While dedicated web and mobile interfaces are envisioned for future production stages, a basic console-based user interface (`ConsoleApp`) is sufficient for prototype demonstration.

| ID | Requirement | Origin |
|:---|:---|:---|
| USA-01 | The console interface should provide clear, descriptive navigation menus aligned with the permissions of the authenticated user role. | Proposed |
| USA-02 | The application should display understandable, actionable error messages whenever input validation fails or an operation cannot be completed. | Proposed |
| USA-03 | The application should validate all mandatory input fields (e.g., NHS number, citizen card number, TIF) before persisting a registration or update. | Proposed |
| USA-04 | The user interface should strictly use terminology consistent with the Project Glossary, Use Case Diagram, and Domain Model. | Proposed |
| USA-05 | The application should present explicit confirmation prompts and success feedback messages upon completing relevant state-modifying operations. | Proposed |
| USA-06 | The application should allow users to cancel an operation before committing changes to the persistence layer. | Proposed |

### 3.1 Usability Considerations

The console interface must prioritize workflow clarity, data consistency, and robust input validation over visual complexity. All screen prompts, outputs, and menu options must be presented in English.

## 4. Reliability

Reliability is critical because the system manages sensitive clinical records and laboratory analysis results.

| ID | Requirement | Origin |
|:---|:---|:---|
| REL-01 | The system shall ensure that no data is lost in the event of an unexpected failure or abnormal termination. | Specified |
| REL-02 | The overall annual system availability shall exceed 99%. | Specified |
| REL-03 | Persistence operations should be transactional, ensuring that no partially inconsistent records remain after a failure. | Derived |
| REL-04 | The system should validate referential integrity between related entities (`RegisteredTest`, `Sample`, `ChemicalAnalysis`, `ParameterResult`, and `Report`). | Derived |
| REL-05 | The system should detect and report communication failures with external services (such as the Barcode Generation API or notification gateways). | Proposed |
| REL-06 | The system should provide recovery mechanisms that preserve previously committed transactional data upon reboot. | Proposed |

### 4.1 Data Integrity

The system must guarantee the consistency and persistence of information associated with clients, registered tests, biological samples, parameter measurements, and medical reports.

Transactional boundaries must prevent partial updates, specifically during sample registration, results recording, and report validation.

### 4.2 Availability Verification

Annual availability exceeding 99% must be supported through resilient software architecture, fault-tolerant persistence, and rapid restart capabilities.

## 5. Performance

The system must comply with strict startup and response time limits established in the Project Assignment.

| ID | Requirement | Origin |
|:---|:---|:---|
| PER-01 | The system shall complete its startup procedure in less than 10 seconds. | Specified |
| PER-02 | The system shall provide a maximum response time of 5 seconds for any request, regardless of load conditions. | Specified |
| PER-03 | The system architecture shall handle peak operating loads while maintaining the 5-second response time threshold. | Specified |
| PER-04 | Representative automated performance and load benchmarks should be defined to measure key operational workflows. | Proposed |

### 5.1 Acceptance Criteria

- **Startup Time:** The elapsed time between process launch and readiness to handle user requests must be strictly under 10 seconds.
- **Response Time:** The duration between request submission and response presentation must not exceed 5 seconds under all evaluated operating scenarios.

## 6. Supportability

The software product must be designed for long-term maintainability, adaptability, and testability.

| ID | Requirement | Origin |
|:---|:---|:---|
| SUP-01 | The system shall be designed to support multiple persistence mechanisms, including relational, NoSQL, and in-memory databases. | Specified |
| SUP-02 | The system shall easily support different test types (`TestType`) measuring one (e.g., COVID-19) or multiple parameters (`Parameter`), with optional reference ranges (`ReferenceRange`). | Specified |
| SUP-03 | All project artifacts, source code, commit messages, and documentation shall be developed strictly in English. | Specified |
| SUP-04 | Automated regression testing shall be adopted across all core components, implemented using the Google Testing Framework (GoogleTest). | Specified recommendation |
| SUP-05 | The architecture should enforce separation of concerns, decoupling domain business logic from UI, persistence, and external APIs. | Proposed |
| SUP-06 | The domain model and service components should be highly cohesive and loosely coupled. | Proposed |

## 7. Additional Constraints (+)

### 7.1 Design Constraints

| ID | Requirement | Origin |
|:---|:---|:---|
| DES-01 | The core application shall be developed in C++. | Specified |
| DES-02 | The system shall be structured into a server-side core application responsible for business logic, persistence, and API exposure. | Specified |
| DES-03 | A basic console-based user interface (`ConsoleApp`) is sufficient for prototype demonstration during the initial phases. | Specified |
| DES-04 | Dedicated web and mobile user interfaces are outside the scope of the current prototype. | Specified |
| DES-05 | The design should use the CLion IDE as the preferred development environment. | Specified recommendation |

### 7.2 Implementation Constraints

| ID | Requirement | Origin |
|:---|:---|:---|
| IMP-01 | All source code, documentation, and diagrams shall be written in English. | Specified |
| IMP-02 | GitHub shall be used as the version control system throughout development. | Specified |
| IMP-03 | All project artifacts must be maintained in the Git repository following clean repository management practices. | Specified |
| IMP-04 | All diagram images stored and embedded in the repository documentation shall be in SVG format. | Specified |
| IMP-05 | The repository name shall follow the required convention: `leti-esoft-26-27-[LabClass][TeamNumber]`. | Specified |
| IMP-06 | Team task planning and tracking shall be documented in `TeamMembersAndTasks.md`. | Specified |
| IMP-07 | Unit and integration testing shall use GoogleTest, structured in the `CoreTests` module. | Specified recommendation |
| IMP-08 | The project build configuration and dependency management shall be managed using CMake. | Specified |

### 7.3 Interface Constraints

| ID | Requirement | Origin |
|:---|:---|:---|
| INT-01 | The system shall integrate with an external Barcode Generation API to automatically generate barcodes for collected samples (`Sample`). | Specified |
| INT-02 | The system shall integrate with external notification services to dispatch SMS and/or email notifications to clients upon report availability. | Specified |
| INT-03 | The core business logic and persistence engine shall expose a dedicated Library API (`UKLabsMS Library API`) consumed directly by the `ConsoleApp`. | Specified |
| INT-04 | The system architecture shall be prepared to expose a REST API (`UKLabsMS REST API`) and a Mobile API (`UKLabsMS Mobile API`) for future client applications. | Specified |
| INT-05 | The business logic layer shall interact with data storage through an abstracted Persistence API (`Persistence API`), isolating persistence technology from business rules. | Specified |
| INT-06 | Generic HTTP client tools (such as Postman) may be used to verify and validate exposed REST endpoints. | Specified option |

### 7.4 Physical Constraints

The Project Assignment does not specify mandatory physical server dimensions or dedicated hardware. The system shall run in execution environments capable of fulfilling the availability (>99%), startup (<10s), and response time (<5s) thresholds.

### 7.5 Legal and Regulatory Constraints

| ID | Requirement | Origin |
|:---|:---|:---|
| LEG-01 | Patient registration and clinical records must comply with National Healthcare Service (NHS) guidelines and English healthcare regulations. | Specified |
| LEG-02 | The system shall enforce territorial exclusivity for COVID-19 testing, ensuring COVID-19 tests are registered exclusively at the authorized subset of clinical analysis laboratories (enforcing Business Rule BR01). | Specified |

## 8. Open Issues and Clarifications

| ID | Open Issue |
|:---|:---|
| OI-01 | What quantitative concurrent user load should be considered representative of peak operating hours? |
| OI-02 | What scheduled maintenance windows are permitted when evaluating the 99% annual availability requirement? |
| OI-03 | What specific third-party providers or protocol standards will be designated for the Barcode Generation API and notification gateways? |
| OI-04 | Which database technology (relational, NoSQL, or in-memory) will be prioritized for initial end-to-end evaluation? |

## 9. References

- LETI-ESOFT 2026/2027 — Project Assignment.
- LETI-ESOFT 2026/2027 — Project Sprint 1.
- UKLabsMS — Use Case Diagram (`use-case-diagram.md`).
- UKLabsMS — OO Analysis & Domain Model (`analysis.md`).
- UKLabsMS — Project Glossary (`glossary.md`).