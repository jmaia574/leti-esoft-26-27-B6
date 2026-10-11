
# Supplementary Specification (FURPS+)

**Project:** UK Labs Management System (UKLabsMS)  
**Course:** LETI-ESOFT 2026/2027  
**Team:** B6  
**Sprint:** 1

## 1. Introduction

This document specifies the supplementary functional and non-functional requirements of the UK Labs Management System (UKLabsMS), using the FURPS+ classification.

It complements the Use Case Diagram and the corresponding User Stories by describing cross-cutting functionality, quality attributes, and project constraints.

Requirements are classified according to their origin:

- **Specified:** Explicitly stated in the Project Assignment.
- **Derived:** Inferred from the business processes and rules described in the Project Assignment.
- **Proposed:** Additional recommendations requiring stakeholder validation.

The term "shall" denotes a requirement, while "should" indicates a recommendation. Proposed requirements are not considered approved unless validated by the stakeholder.

## 2. Functionality

This section specifies functionality shared across multiple use cases or not exclusively associated with a particular use case, including security and information access.

| ID | Requirement | Origin |
|:---|:---|:---|
| FUN-01 | All system users shall be authenticated before accessing the application. Authentication may be simulated during the prototype stage. | Specified |
| FUN-02 | The system shall prevent clients from accessing analysis results until the specialist doctor has prepared the corresponding report. | Specified |
| FUN-03 | After the specialist doctor completes the diagnosis, the system shall notify the client by SMS and/or email that the analysis results and report are available. | Specified |
| FUN-04 | The system shall support sorting clinical analysis results by the client's TIF or name. | Specified |
| FUN-05 | The system shall maintain associations between registered tests, clients, collected samples, analysis results, and reports. | Derived |
| FUN-06 | The system should restrict operations according to the responsibilities of each user role. | Proposed |
| FUN-07 | The system should prevent clients from accessing another client's private clinical information. | Proposed |
| FUN-08 | The system should maintain an audit trail of relevant changes to clinical information, including the responsible user and timestamp. | Proposed |

### 2.1 Security

Clinical information is sensitive and should be protected against unauthorized disclosure or modification.

The application should distinguish authentication from authorization. Authentication identifies the user, while authorization determines which operations and information the user may access.

During prototype development, authentication may be simulated, as permitted by the Project Assignment.

### 2.2 Functional Traceability

- FUN-01 relates to UC01 (Authenticate User).
- FUN-02 relates to UC11 and UC13.
- FUN-03 relates to UC12.
- FUN-04 relates to UC13 and result consultation.
- FUN-05 applies across UC06 to UC11.
- FUN-06 to FUN-08 are proposed cross-cutting enhancements.

## 3. Usability

The Project Assignment allows a basic console-based user interface for demonstration purposes. Dedicated web and mobile interfaces are envisioned for future development but are outside the current prototype scope.

The following requirements are proposed usability improvements.

| ID | Requirement | Origin |
|:---|:---|:---|
| USA-01 | The console interface should provide clear, descriptive options corresponding to the operations available to the authenticated user. | Proposed |
| USA-02 | The application should display understandable error messages when input is invalid or an operation cannot be completed. | Proposed |
| USA-03 | The application should validate required input fields before accepting a registration or update operation. | Proposed |
| USA-04 | The interface should use consistent terminology aligned with the project glossary. | Proposed |
| USA-05 | The application should provide confirmation messages after successfully completing relevant operations. | Proposed |
| USA-06 | The application should allow users to cancel an operation before committing changes, where applicable. | Proposed |

### 3.1 Usability Considerations

The prototype should prioritize clarity, consistency, and error prevention rather than visual complexity.

The terminology used in the interface should remain consistent with the Glossary and the Domain Model.

## 4. Reliability

Reliability is particularly important because the system manages clinical information and must preserve recorded data.

| ID | Requirement | Origin |
|:---|:---|:---|
| REL-01 | The system shall ensure that no data is lost in the event of a failure. | Specified |
| REL-02 | The overall annual system availability shall exceed 99%. | Specified |
| REL-03 | The system should ensure that registration and update operations do not leave partially inconsistent records after a failure. | Derived |
| REL-04 | The system should detect invalid or inconsistent references between related clinical records. | Derived |
| REL-05 | The system should provide mechanisms for detecting and reporting failures in external service communication. | Proposed |
| REL-06 | The system should support recovery procedures that preserve previously committed data. | Proposed |

### 4.1 Data Integrity

The system shall preserve the integrity of information related to clients, registered tests, samples, parameters, analysis results, and diagnostic reports.

Persistence operations should avoid incomplete or inconsistent modifications, particularly when failures occur during an operation.

### 4.2 Availability

Annual availability must exceed 99%, as specified in the Project Assignment.

The precise operational conditions, planned maintenance policy, and method of measuring availability should be clarified with the stakeholder.

### 4.3 Verification

Reliability testing should include:

- Simulated failures during data modification.
- Verification that previously committed information remains available.
- Validation of relationships between related records.
- Verification of recovery behavior after unexpected termination.

## 5. Performance

The Project Assignment establishes explicit requirements for start-up time and response time.

| ID | Requirement | Origin |
|:---|:---|:---|
| PER-01 | The system shall start in less than 10 seconds. | Specified |
| PER-02 | The system shall provide a maximum response time of 5 seconds, regardless of load conditions. | Specified |
| PER-03 | The system shall be designed to handle high loads during peak operating periods while respecting the response-time requirement. | Specified |
| PER-04 | The team should define representative performance tests covering the main system operations. | Proposed |

### 5.1 Start-up Performance

**Acceptance criterion:** The elapsed time between initiating system start-up and the system becoming ready to process requests must be strictly less than 10 seconds.

### 5.2 Response Time

**Acceptance criterion:** The elapsed time between receiving a request and providing its response must not exceed 5 seconds under the evaluated load conditions.

### 5.3 Load Considerations

The Project Assignment refers to high peak loads but does not define a specific number of simultaneous users or requests.

A representative workload must therefore be agreed upon before quantitative load testing.

No maximum memory consumption or CPU utilization value is explicitly specified.

## 6. Supportability

The application must be designed with maintainability and adaptability in mind, particularly regarding future technology and business changes.

| ID | Requirement | Origin |
|:---|:---|:---|
| SUP-01 | The system shall be designed to support data persistence using relational, NoSQL, and in-memory databases. | Specified |
| SUP-02 | The system shall be designed to support different test types containing one or multiple parameters. | Specified |
| SUP-03 | Project artifacts and source code shall be developed in English. | Specified |
| SUP-04 | The project should include automated regression tests, preferably using the Google Testing Framework. | Specified recommendation |
| SUP-05 | The architecture should separate business logic from infrastructure-specific persistence mechanisms. | Proposed |
| SUP-06 | The implementation should favor modular and maintainable components. | Proposed |
| SUP-07 | The system should allow the addition of new test types without significant changes to unrelated functionality. | Derived |

### 6.1 Maintainability

The project should follow software engineering principles that promote readability, modularity, and low coupling.

Clear responsibility boundaries should be established between domain logic, application services, persistence mechanisms, and user interaction.

### 6.2 Testability

Automated tests should verify business rules, data validation, and relevant system behavior.

Google Test is the preferred testing framework recommended in the Project Assignment.

## 7. Additional Constraints (+)

### 7.1 Design Constraints

| ID | Requirement | Origin |
|:---|:---|:---|
| DES-01 | The core application shall be developed in C++. | Specified |
| DES-02 | The system shall include a core server-side application responsible for maintaining data, enforcing business logic, and exposing APIs to client applications. | Specified |
| DES-03 | A basic console-based user interface is sufficient for prototype demonstration. | Specified |
| DES-04 | Dedicated web and mobile applications are outside the current prototype development scope. | Specified |
| DES-05 | The design should support separation between the core application and client-facing applications. | Derived |
| DES-06 | The project should use CLion as the preferred development environment. | Specified recommendation |

### 7.2 Implementation Constraints

| ID | Requirement | Origin |
|:---|:---|:---|
| IMP-01 | All project artifacts, including source code, shall be written in English. | Specified |
| IMP-02 | GitHub shall be used as the version control system throughout project development. | Specified |
| IMP-03 | Source code, documentation, diagrams, configuration files, and other project artifacts shall be maintained in the repository. | Specified |
| IMP-04 | Images stored in the repository shall use SVG format. | Specified |
| IMP-05 | The repository name shall follow the convention leti-esoft-26-27-[LabClass][TeamNumber]. | Specified |
| IMP-06 | Team tasks shall be planned and documented using the TeamMembersAndTasks.md template. | Specified |
| IMP-07 | The team should adopt automated regression testing, preferably using Google Test. | Specified recommendation |

### 7.3 Interface Constraints

| ID | Requirement | Origin |
|:---|:---|:---|
| INT-01 | The system shall use an external API to generate barcodes for collected samples. | Specified |
| INT-02 | The system shall support notifying clients by SMS and/or email when results become available. | Specified |
| INT-03 | The core application shall expose APIs to support client-side applications. | Specified |
| INT-04 | Generic HTTP client tools, such as Postman, may be used to verify and validate the exposed APIs. | Specified option |
| INT-05 | The system should handle external API failures without corrupting existing clinical information. | Proposed |
| INT-06 | The interfaces used for barcode generation and notifications should be abstracted to reduce dependence on specific providers. | Proposed |

### 7.4 Physical Constraints

The Project Assignment does not specify mandatory hardware characteristics, physical dimensions, or particular deployment equipment.

The system is expected to operate in an environment capable of supporting the required availability, persistence, and performance characteristics.

Hardware capacity, operating system requirements, storage capacity, and network infrastructure should be determined in later stages according to the selected deployment architecture.

No additional mandatory physical constraints are assumed during Sprint 1.

## 8. Open Issues and Clarifications

The following matters require additional clarification or future design decisions:

| ID | Open Issue |
|:---|:---|
| OI-01 | What number of simultaneous users or requests should be considered representative of peak load? |
| OI-02 | What operational conditions and maintenance periods should be considered when measuring annual availability? |
| OI-03 | Which authentication and authorization mechanisms are expected beyond the prototype stage? |
| OI-04 | Which external providers or technical protocols should be used for barcode generation and client notifications? |
| OI-05 | Which persistence technologies will be used to demonstrate support for relational, NoSQL, and in-memory databases? |
| OI-06 | What are the expected procedures for recovering data and service after a failure? |

## 9. References

- LETI-ESOFT 2026/2027 - Project Assignment.
- LETI-ESOFT 2026/2027 - Project Sprint 1.
- UKLabsMS Use Case Diagram.
- UKLabsMS Glossary.
