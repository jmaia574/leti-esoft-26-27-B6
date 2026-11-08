
# Use Case Diagram (UCD)

## 1. Introduction

This document presents the Use Case Diagram of the UK Labs Management System (UKLabsMS), developed during Sprint 1 of the LETI-ESOFT 2026/2027 project.

The diagram identifies the main system actors, functional requirements, and interactions derived from the UK Labs Project Assignment.

The use cases represent the system's initial functional scope. Sprint 2 US10-US13 refine selected administration capabilities, as mapped in Section 4. `UC` identifiers in this document and `US` identifiers in the Sprint 2 folders are separate numbering schemes.

## 2. Use Case Diagram

![UKLabsMS Use Case Diagram](svg/UCD.svg)

## 3. Actors

| Actor                           | Description |
|:--------------------------------|:---|
| Staff Member                    | Generalized actor representing operational UK Labs staff who interact with the system. |
| Administrator                   | Separate actor who manages the core information necessary for the system's operation. |
| Receptionist                    | Registers clients and prescribed clinical tests. |
| Medical Lab Technician          | Collects biological samples and records them in the system. |
| Clinical Chemistry Technologist | Performs chemical analyses and records the obtained results. |
| Specialist Doctor               | Reviews analysis results, establishes diagnoses, and prepares diagnostic reports. |
| Client                          | Consults clinical analysis results and diagnostic reports after they become available. |
| Barcode Generation API          | External system responsible for automatically generating barcodes for collected samples. |

## 4. Business Use Cases and Sprint 2 Stories

| Use Case    | Description                           |
|:------------|:--------------------------------------|
| UC01 | Authenticate User                     |
| UC02 | Manage Clinical Analysis Laboratories |
| UC03 | Manage Employees                      |
| UC04 | Manage Test Types                     |
| UC05 | Manage Parameters                     |
| UC06 | Register Client                       |
| UC07 | Register Prescribed Test              |
| UC08 | Register Sample                       |
| UC09 | Obtain Sample Barcode                 |
| UC10 | Record Chemical Analysis Results      |
| UC11 | Prepare Diagnostic Report             |
| UC12 | View Test Results and Report          |

The UC identifiers are the team's business-scope organization, not aliases for assignment user-story numbers. The Sprint 2 refinements are:

| Sprint 2 User Story | Business Use Case | Integration |
|:---|:---|:---|
| [US10 - Register a Test Type](../US10/US10.md) | UC04 - Manage Test Types | Supplies Test Type catalog entries. Linking them to Parameters through TestTypeParameter remains a separate configuration responsibility. |
| [US11 - Register a Parameter](../US11/US11.md) | UC05 - Manage Parameters | Supplies Parameter catalog entries and applicable reference values for shared use by test definitions. |
| [US12 - Register an Employee](../US12/US12.md) | UC03 - Manage Employees | Creates the Employee records that the shared repository will make available to US13. |
| [US13 - List Employees by Role](../US13/US13.md) | UC03 - Manage Employees | Reads the same Employee records without modifying them. |

In particular, UC10 is not US10, UC11 is not US11, and UC12 is not US12. The diagram notes show this refinement mapping; they do not assert additional UML include or extend relationships between the stories. [The integration overview](../README.md) distinguishes this intended design from the current implementation gaps.

## 5. Use Case Relationships

### Actor Generalization

The Receptionist, Medical Lab Technician, Clinical Chemistry
Technologist, and Specialist Doctor are specializations of the
Staff Member actor. The Administrator is a separate actor, not a
Staff Member, and authenticates independently.

This generalization represents their shared role as
UK Labs employees while preserving their specific
responsibilities.

### Include Relationship

UC08 (Register Sample) includes UC09
(Obtain Sample Barcode).

Every collected sample must be identified using a barcode
automatically generated through an external API.

### Authentication

Authentication is a prerequisite for accessing the system.

The authentication mechanism may be simulated during
the prototype development stage, as specified in the
Project Assignment.

## 6. Business Rules

| ID | Business Rule |
|:---|:---|
| BR01 | Only a subset of UK Labs clinical analysis laboratories performs COVID-19 tests. |
| BR02 | Each registered test is associated with a client, a test type, the prescribed parameters, a prescription date, a sample collection date, and a collection laboratory. |
| BR03 | Every collected sample is associated with a registered test and identified by an automatically generated barcode. |
| BR04 | Chemical analysis results include the obtained value and the analysis date and time for each measured parameter. |
| BR05 | Clients may access their analysis results only after a specialist doctor has prepared the diagnostic report. |
| BR06 | After the specialist doctor completes the diagnosis and report, the system sends an SMS and/or email notification informing the client that the results are available. |

## 7. Modeling Decisions and Assumptions

- The use cases are organized by functional responsibility.
- The distinction between test types and registered tests is preserved.
- The Barcode Generation API is modeled as an external system because the Project Assignment explicitly requires this integration.
- Authentication is represented as a general system function rather than included in every individual use case.
- Client notification is modeled as an automatic system behavior following the completion of the diagnostic report (UC11), rather than as a separate use case.
- UC12 represents the client's ability to view test results and the diagnostic report once they become available.
- UC01 to UC12 are identifiers proposed by the team for requirements organization and traceability, distinct from the Sprint 2 user-story identifiers.

## 8. References

- LETI-ESOFT 2026/2027 - Project Assignment.
- LETI-ESOFT 2026/2027 - Project Sprint 1.
- [UKLabsMS Project Glossary](glossary.md).
- [Shared Domain Model](analysis.md).
- [Sprint 2 Integration Overview](../README.md).
