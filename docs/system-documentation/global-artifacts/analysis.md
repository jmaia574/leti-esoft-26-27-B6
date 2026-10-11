# OO Analysis — UKLabsMS Domain Model

## 1. Purpose and scope

This document explains the identification of conceptual classes and associations in the UK Labs Management System (UKLabsMS) domain model for Sprint 1. The model is derived primarily from Section 2.1 (*Business Context*) of the **LETI-ESOFT 2026/2027 Project Assignment**. It represents business concepts, not C++ implementation classes, user interfaces, database tables or the chronological order of operations.

The domain model is preliminary. Some multiplicities and concepts are based on **explicit modeling assumptions**, identified below, because the assignment does not fully define every business constraint.

## 2. Rationale to identify domain conceptual classes

The following candidates were identified using nouns and noun phrases in the assignment, grouped by conceptual-class categories suggested by *Applying UML and Patterns* (Craig Larman).

| Conceptual class category | Identified concepts | Rationale |
|:---|:---|:---|
| Business transactions / records | `RegisteredTest`, `ChemicalAnalysis` | A test is registered for a client; a chemical analysis is performed and its results recorded. |
| Transaction-related documents | `LabOrder`, `Report` | The client presents a doctor's prescription; the specialist doctor produces a diagnostic report. |
| Roles of people | `Client`, `Receptionist`, `MedicalLabTechnician`, `ClinicalChemistryTechnologist`, `SpecialistDoctor`, `Administrator`, `Courier` | These represent distinct participants in the laboratory workflow or management of core information. `Courier` participates in physical sample delivery, though software tracking of couriers is not specified. |
| Places | `ClinicalAnalysisLaboratory`, `ChemicalLaboratory` | Samples are collected at laboratories across England and analyzed at the central chemical laboratory. |
| Descriptions of services | `TestType`, `Parameter`, `ReferenceRange` | A test type defines the kind of test, measurable parameters, and optional reference limits. |
| Physical objects | `Sample` | Biological samples are collected, associated with registered tests, and identified by barcodes. |
| Records of measured values | `ParameterResult` | For each measured parameter, a value and analysis date/time are recorded. |
| Clinical conclusions | `Diagnosis` | A specialist doctor interprets the results and establishes a diagnosis. |
| Communications | `Notification` | The client is informed by SMS and/or e-mail once results are available. |

**Conceptual-class distinction:** `TestType` describes a type of examination available in the catalogue; `RegisteredTest` represents a particular prescribed examination registered for an individual client. `Parameter` defines what may be measured; `ParameterResult` records the value obtained in an actual analysis.

**Not modeled as conceptual classes:** the user interface, C++ controllers, API calls, and the barcode-generation service. The barcode is represented as an attribute of `Sample`; the external API is an integration relevant to the Use Case Diagram and subsequent design, not necessarily a persistent domain entity.

## 3. Rationale to identify associations

Associations were selected when the assignment describes a meaningful business link between concepts, based on the general association patterns described by Larman (e.g., *contains*, *records*, *describes*, *performs*, or *is associated with*).

| Concepts | Association | Reason |
|:---|:---|:---|
| `Client` — `LabOrder` | submits | A client arrives with a medical prescription. |
| `Client` — `RegisteredTest` | is associated with | Registered clinical tests concern individual clients. |
| `Receptionist` — `RegisteredTest` | registers | Receptionists enter prescribed tests into the application. |
| `LabOrder` — `RegisteredTest` | corresponds to | A prescription is the basis for registering the prescribed examination. |
| `RegisteredTest` — `TestType` | is classified as | Each registered test has a specific test type. |
| `ClinicalAnalysisLaboratory` — `RegisteredTest` | collects samples for | The test records the laboratory at which samples are collected. |
| `TestType` — `Parameter` | measures | A type of test involves one or more measurable parameters. |
| `Parameter` — `ReferenceRange` | has | Some parameters have optional minimum and maximum reference values. |
| `RegisteredTest` — `Sample` | has | Collected samples are recorded against the registered test. |
| `MedicalLabTechnician` — `Sample` | registers | Technicians collect and record the samples. |
| `Courier` — `Sample` | transports | Samples are delivered by courier to the central laboratory. |
| `Sample` — `ChemicalAnalysis` | undergoes | Chemical analyses are performed on samples. |
| `ChemicalLaboratory` — `ChemicalAnalysis` | hosts | Chemical analyses are performed in the central chemical laboratory. |
| `ClinicalChemistryTechnologist` — `ChemicalAnalysis` | performs | The technologist performs the analysis and records its results. |
| `ChemicalAnalysis` — `ParameterResult` | records | Chemical analysis yields the measured results. |
| `Parameter` — `ParameterResult` | measured by | Every recorded measured value corresponds to a parameter definition. |
| `RegisteredTest` — `Report` | results in | A report becomes available after interpretation of the test results. |
| `Report` — `Diagnosis` | contains | The specialist doctor's diagnosis is included in the report. |
| `Report` — `ParameterResult` | presents | The report makes the analysis results available to the client. |
| `SpecialistDoctor` — `Report` | prepares | The specialist doctor prepares the diagnostic report. |
| `Client` — `Notification` | receives | Clients receive notifications that their results are available. |
| `Notification` — `Report` | concerns | A notification refers to an available report. |
| `Administrator` — core catalog information | manages | Administrators are responsible for managing test types, parameters, and laboratories. |

## 4. Multiplicity decisions and assumptions

- **`Client "1" -- "0..*" LabOrder`**: a client can be registered before any lab order has been recorded. Each modeled lab order belongs to one client.
- **`Client "1" -- "0..*" RegisteredTest`**: a client may have no registered tests yet, or many over time; each test concerns one client.
- **`LabOrder "1" -- "1" RegisteredTest`**: **assumption** for the initial model: one lab order corresponds to one registered test. The assignment refers to the prescribed test type in the singular; support for multi-test lab orders would require clarification.
- **`RegisteredTest "0..*" -- "1" TestType`**: a catalogue test type may exist without any registered tests, but each registered test has one defined type.
- **`TestType "0..*" -- "1..*" Parameter`**: every test type involves at least one parameter; **assumption**: parameters can be reused across test types and can be registered before any type uses them.
- **`RegisteredTest "1" -- "0..*" Sample`**: tests can exist before sample collection; each collected sample is associated with one registered test.
- **`Sample "1" -- "0..*" ChemicalAnalysis`**: **assumption**: an already collected sample can be reanalyzed, for example for verification; the assignment does not explicitly require repeated analyses.
- **`RegisteredTest "1" -- "0..1" Report`**: the report does not exist until a specialist doctor prepares it; the initial model supports one report per registered test.
- **`Parameter "1" -- "0..1" ReferenceRange`**: reference values are optional, as explicitly stated in the assignment.
- **`Courier "0..1" -- "0..*" Sample`**: **assumption**: courier assignment is optional before shipment, and at most one courier is recorded for each sample; the assignment does not explicitly require tracking courier assignments.
- **Administrator relationships** denote management responsibility only, not exclusive ownership by a specific administrator. They are therefore modeled with optional many-to-many multiplicities.

### Business rule not expressed by a class association alone

Clients must only be allowed to access analysis results once the specialist doctor has prepared the report. This temporal/access rule belongs in requirements documentation and the associated use-case behavior, rather than being inferred from an association alone.

## 5. Domain Model

![UKLabsMS Domain Model](svg/DM.svg)

The diagram is generated from `puml/DM.puml`. Both the source and exported SVG must be committed to the repository.

## 6. References

- LETI-ESOFT 2026/2027 — Project Assignment, Section 2.1 (*Business Context*).
- Craig Larman, *Applying UML and Patterns*, conceptual-class categories and common-association patterns.
