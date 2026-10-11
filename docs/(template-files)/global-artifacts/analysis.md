
# OO Analysis

**Project:** UK Labs Management System (UKLabsMS)  
**Course:** LETI-ESOFT 2026/2027  
**Team:** B6  
**Sprint:** 1

## 1. Introduction

This document presents the object-oriented analysis of the UK Labs Management System (UKLabsMS), focusing on the identification of domain conceptual classes, their attributes, and the associations between them.

The analysis is based on the UK Labs Project Assignment and the Domain Model developed by Team B6.

Conceptual classes were identified by examining the relevant nouns and noun phrases in the business description. Associations were identified by analyzing relationships and verbs that express meaningful connections between domain concepts.

The conceptual class categories follow the approach described in "Applying UML and Patterns: An Introduction to Object-Oriented Analysis and Design and Iterative Development".

The purpose of the Domain Model is to represent the main business concepts and their relationships, independently of implementation details.

## 2. Rationale to Identify Domain Conceptual Classes

### 2.1 Conceptual Class Category List

The following classification organizes the conceptual classes identified in the existing Domain Model.

A conceptual class may be relevant to more than one category. For clarity, each class is assigned to its most representative category.

### Business Transactions

- **RegisteredTest** - Represents a clinical test registered for a client, associated with prescription and sample collection information.

### Transaction Line Items

No independent transaction line item class is identified in the current Domain Model.

### Product/Service Related to a Transaction or Transaction Line Item

- **TestType** - Represents a type of clinical test offered by UK Labs, identified by an internal code, NHS code, and collection method description.

### Transaction Records

- **ParameterResult** - Represents the result obtained for a measured parameter, including the recorded value and timestamp.

### Roles of People or Organizations

- **Client** - Person receiving clinical analysis services, identified through personal, healthcare, and contact information.
- **Administrator** - Staff member responsible for configuring test types and parameters and managing clinical analysis laboratories.
- **Receptionist** - Staff member responsible for registering prescribed clinical tests.
- **MedicalLabTechnician** - Healthcare professional responsible for collecting samples.
- **ClinicalChemistryTechnologist** - Professional responsible for performing chemical analyses and recording their results.
- **SpecialistDoctor** - Doctor responsible for examining results and preparing diagnostic reports.
- **Courier** - Person responsible for transporting collected samples to the chemical laboratory.

### Places

- **ClinicalAnalysisLaboratory** - Laboratory where clients are received, tests are registered, and samples are collected.
- **ChemicalLaboratory** - Central laboratory where chemical analyses are performed.

### Noteworthy Events

- **ChemicalAnalysis** - Represents the chemical analysis of a collected sample, performed to obtain parameter results.

### Physical Objects

- **Sample** - Biological material collected from a client, such as blood, urine, or a swab, identified by a barcode.

### Descriptions of Things

- **Parameter** - Defines a measurable characteristic associated with a test type, identified by code, name, description, and metric.
- **ReferenceRange** - Represents the minimum and maximum reference values associated with a parameter, when applicable.

### Catalogs

The current Domain Model does not introduce an independent catalog class.

TestType and Parameter represent configurable definitions, but no separate catalog entity is modeled.

### Containers

No independent container class is identified in the current Domain Model.

### Elements of Containers

No separate conceptual class is identified specifically as a container element.

### (Other) Organizations

UK Labs is the organization responsible for the laboratory network, but it is not represented as a separate conceptual class in the current Domain Model.

### Other (External/Collaborating) Systems

The external barcode generation API is part of the business context but is not represented as a conceptual class.

It is an external technical integration rather than a central business-domain concept.

### Records of Finance, Work, Contracts, Legal Matters

No specific class is identified in the current model for this category.

### Financial Instruments

No financial instruments are described within the current scope of the UKLabsMS Domain Model.

### Documents Mentioned/Used to Perform Some Work

- **LabOrder** - Represents the medical prescription specifying the tests and parameters requested by a doctor.
- **Report** - Represents the diagnostic report prepared by a specialist doctor after examining analysis results.

### Additional Domain Concepts

The following concepts do not fit exclusively into the previous categories:

- **Diagnosis** - Represents the medical assessment established by a specialist doctor and contained in a report.
- **Notification** - Represents an alert associated with an available diagnostic report and received by a client.

## 3. Rationale for the Identification of Conceptual Classes

The following table explains why the conceptual classes are relevant to the application domain.

| Conceptual Class | Rationale |
|:---|:---|
| Client | Required to identify the person receiving clinical services and associate tests with personal information. |
| Administrator | Represents the responsibility for maintaining core system information. |
| Receptionist | Represents the professional role responsible for test registration. |
| MedicalLabTechnician | Required to identify the professional responsible for sample collection. |
| ClinicalChemistryTechnologist | Represents the professional performing chemical analyses. |
| SpecialistDoctor | Represents the professional responsible for medical diagnosis and reporting. |
| Courier | Represents the role responsible for transporting collected samples. |
| ClinicalAnalysisLaboratory | Required to identify the collection location and its business information. |
| ChemicalLaboratory | Represents the central location where chemical analyses are performed. |
| LabOrder | Represents the medical prescription supporting test registration. |
| RegisteredTest | Represents an individual clinical test registered for a client. |
| TestType | Defines the characteristics of a test offered by UK Labs. |
| Parameter | Represents a characteristic measured during a clinical test. |
| ReferenceRange | Represents reference minimum and maximum values, when applicable. |
| Sample | Represents the biological material collected for analysis. |
| ChemicalAnalysis | Represents the laboratory analysis process associated with samples. |
| ParameterResult | Represents a measured result recorded during chemical analysis. |
| Diagnosis | Represents the medical interpretation of the analysis results. |
| Report | Represents the document prepared by the specialist doctor. |
| Notification | Represents the communication informing a client that results are available. |

## 4. Identification of Conceptual Class Attributes

Attributes describe relevant information associated with each conceptual class.

The following attributes correspond to those represented in the existing Domain Model.

| Conceptual Class | Attributes |
|:---|:---|
| Client | name, citizenCardNumber, nhsNumber, birthDate, sex, taxIdentificationNumber, phoneNumber, email |
| ClinicalAnalysisLaboratory | code, address, phoneNumber, email, openingHour, closingHour |
| RegisteredTest | dateOfPrescription, sampleCollectionDate |
| TestType | internalCode, nhsCode, collectionMethodDescription |
| Parameter | code, name, description, metric |
| ReferenceRange | minimum, maximum |
| Sample | barcode |
| ParameterResult | value, recordedAt |

The remaining conceptual classes do not have explicitly represented attributes in the current diagram.

This does not necessarily mean that these concepts have no relevant properties. Additional attributes may be identified as requirements are clarified.

Some concepts may also require identifiers in a future design model. Such implementation decisions are outside the scope of the present conceptual analysis.

## 5. Rationale to Identify Associations Between Conceptual Classes

An association represents a meaningful relationship between domain concepts.

Associations were identified by examining the business processes described in the Project Assignment, including client registration, prescribed tests, sample collection, chemical analysis, medical reporting, and administration.

The table below reproduces the associations represented in the existing Domain Model.

### 5.1 Association Identification

| Concept (A) | Association | Concept (B) |
|:---|:---|:---|
| Client | submits | LabOrder |
| Client | is performed on | RegisteredTest |
| Receptionist | registers | RegisteredTest |
| LabOrder | contains | RegisteredTest |
| RegisteredTest | is classified as | TestType |
| ClinicalAnalysisLaboratory | collects at | RegisteredTest |
| TestType | measures | Parameter |
| Parameter | includes | ReferenceRange |
| RegisteredTest | requires | Sample |
| MedicalLabTechnician | collects | Sample |
| Courier | transports | Sample |
| Sample | is analyzed in | ChemicalAnalysis |
| ChemicalLaboratory | hosts | ChemicalAnalysis |
| ClinicalChemistryTechnologist | performs | ChemicalAnalysis |
| ChemicalAnalysis | records | ParameterResult |
| Parameter | measured by | ParameterResult |
| RegisteredTest | results in | Report |
| Report | contains | Diagnosis |
| Report | presents | ParameterResult |
| SpecialistDoctor | prepares | Report |
| Client | receives | Notification |
| Notification | concerns | Report |
| Administrator | configures | TestType |
| Administrator | configures | Parameter |
| Administrator | manages | ClinicalAnalysisLaboratory |

### 5.2 Association Rationale

| Association | Rationale |
|:---|:---|
| Client - LabOrder | A medical prescription is presented by a client during the clinical test registration process. |
| Client - RegisteredTest | Each registered test is associated with the client who undergoes the examination. |
| Receptionist - RegisteredTest | The receptionist is responsible for registering prescribed clinical tests. |
| LabOrder - RegisteredTest | The medical prescription provides the information required to register the prescribed tests. |
| RegisteredTest - TestType | Each registered test follows the definition of a specific test type. |
| ClinicalAnalysisLaboratory - RegisteredTest | Each registered test is associated with a clinical analysis laboratory where sample collection is scheduled. |
| TestType - Parameter | A test type defines the parameters that must be measured. |
| Parameter - ReferenceRange | Parameters may have minimum and maximum reference values. |
| RegisteredTest - Sample | Collected samples are associated with the registered clinical test. |
| MedicalLabTechnician - Sample | The technician collects samples and records them in the system. |
| Courier - Sample | Samples are transported from collection laboratories to the central chemical laboratory. |
| Sample - ChemicalAnalysis | Collected samples are examined through chemical analyses. |
| ChemicalLaboratory - ChemicalAnalysis | Chemical analyses are performed at the central chemical laboratory. |
| ClinicalChemistryTechnologist - ChemicalAnalysis | The technologist performs chemical analyses and records their results. |
| ChemicalAnalysis - ParameterResult | Chemical analyses produce recorded parameter results. |
| Parameter - ParameterResult | Each result corresponds to a specific measured parameter. |
| RegisteredTest - Report | A registered test may result in a diagnostic report after its analysis is completed. |
| Report - Diagnosis | The report contains the diagnosis established by the specialist doctor. |
| Report - ParameterResult | The report presents the results associated with the clinical test. |
| SpecialistDoctor - Report | The specialist doctor reviews the analysis results and prepares the report. |
| Client - Notification | The client receives a notification when the results become available. |
| Notification - Report | The notification concerns the availability of a diagnostic report. |
| Administrator - TestType | Administrators maintain the definitions of clinical test types. |
| Administrator - Parameter | Administrators configure the parameters used by clinical tests. |
| Administrator - ClinicalAnalysisLaboratory | Administrators manage the information associated with laboratories. |

## 6. Multiplicity Analysis

Multiplicities specify how many instances of a conceptual class may participate in an association.

The current Domain Model includes multiplicities such as:

- **1** - Exactly one associated instance.
- **0..1** - Zero or one associated instance.
- **0..*** - Zero or more associated instances.
- **1..*** - One or more associated instances.

### 6.1 Main Multiplicity Decisions

**Client and RegisteredTest**

A client can be associated with zero or more registered tests, while each registered test belongs to one client.

This supports the registration of clients who have not yet undergone a clinical test.

**RegisteredTest and TestType**

Each registered test is associated with exactly one test type, while a test type may be associated with several registered tests.

This distinguishes the definition of a test from an individual registered examination.

**TestType and Parameter**

The current model establishes a many-to-many association with a minimum of one at both ends.

This represents test types involving multiple parameters and parameters potentially reused by several test types.

The minimum participation of a parameter in at least one test type is a modeling assumption.

**Parameter and ReferenceRange**

Each parameter may have zero or one reference range, allowing parameters for which minimum and maximum reference values are not applicable.

**RegisteredTest and Sample**

The current model establishes that each registered test requires one or more samples.

However, the lifecycle of a registered test includes a stage before sample collection. Therefore, this multiplicity should be reviewed to determine whether zero samples must be allowed until collection occurs.

**RegisteredTest and Report**

A registered test may have zero or one associated report in the current model.

This represents the period before the specialist doctor prepares the report.

**Report and Diagnosis**

The current model establishes a one-to-one association between a report and a diagnosis.

This is consistent with the intended reporting process but should be confirmed if future requirements introduce multiple diagnoses per report.

## 7. Business Rules Represented in the Domain Model

The Domain Model reflects the following business rules:

**BR-DM-01:** A registered test is associated with a client.

**BR-DM-02:** A registered test is classified according to a defined test type.

**BR-DM-03:** Test types define one or more parameters to be measured.

**BR-DM-04:** Parameters may have minimum and maximum reference values when applicable.

**BR-DM-05:** Biological samples are associated with registered clinical tests.

**BR-DM-06:** Chemical analyses are performed at the central chemical laboratory.

**BR-DM-07:** Analysis results are associated with measured parameters.

**BR-DM-08:** Specialist doctors examine analysis results and prepare diagnostic reports.

**BR-DM-09:** Clients are notified when their results and reports become available.

**BR-DM-10:** A client can access clinical results only after the specialist doctor has prepared the corresponding report.

The last rule is primarily a behavioral and access-control constraint. Its enforcement is not fully represented by a static association in the Domain Model.

## 8. Modeling Assumptions and Issues Requiring Validation

The current Domain Model was developed as an initial conceptual representation of the UK Labs business domain.

The following aspects require further analysis:

**MA-01 - Client and LabOrder multiplicity**

The current model requires each client to have at least one LabOrder.

It should be clarified whether a newly registered client can exist before presenting a prescription.

**MA-02 - LabOrder and RegisteredTest multiplicity**

The model requires each LabOrder to contain at least one RegisteredTest.

The relationship should be reviewed if prescriptions may exist in the system before all associated tests are registered.

**MA-03 - RegisteredTest and Sample multiplicity**

The current model requires one or more samples per registered test.

It should be confirmed whether this rule applies only after sample collection or throughout the entire test lifecycle.

**MA-04 - Sample and ChemicalAnalysis**

The current model associates each sample with at most one chemical analysis.

Additional clarification may be necessary to determine whether one sample can participate in multiple analytical procedures.

**MA-05 - Report and ParameterResult**

The model assumes each report presents one or more parameter results.

The lifecycle of reports and the relationship between results, tests, and reports should be validated.

**MA-06 - COVID-19 testing restrictions**

Only a subset of clinical analysis laboratories performs COVID-19 tests.

The current Domain Model does not explicitly represent which laboratories are authorized to perform these tests.

**MA-07 - Employee management**

The Project Assignment mentions administrative management of employees.

The current model represents individual professional roles but does not introduce a common Employee concept.

**MA-08 - Medical prescription information**

The LabOrder class currently has no attributes.

The placement of prescription-related information should be reviewed to avoid ambiguity between LabOrder and RegisteredTest.

These issues are documented for refinement without changing the existing model at this stage.

## 9. Domain Model

The following diagram represents the conceptual classes, attributes, associations, and multiplicities identified during Sprint 1.

![UKLabsMS Domain Model](svg/DM.svg)

The editable PlantUML source is maintained in:

`puml/DM.puml`

The SVG diagram must be generated from the same PlantUML source to ensure consistency between the documentation and the model.

## 10. Conclusion

The Domain Model provides a conceptual representation of the UKLabsMS business domain.

It captures the main participants, laboratory facilities, test definitions, prescriptions, registered tests, biological samples, chemical analyses, results, diagnoses, reports, and notifications.

The analysis establishes an initial understanding of the business concepts and relationships while identifying assumptions that require further clarification.

The model should be reviewed and refined throughout subsequent sprints in response to stakeholder feedback and evolving requirements.

## 11. References

- LETI-ESOFT 2026/2027 - Project Assignment.
- LETI-ESOFT 2026/2027 - Project Sprint 1.
- UKLabsMS Project Glossary.
- UKLabsMS Use Case Diagram.
- Applying UML and Patterns: An Introduction to Object-Oriented Analysis and Design and Iterative Development.
