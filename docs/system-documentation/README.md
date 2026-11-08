# System Documentation and User-Story Integration

This folder contains requirements engineering, object-oriented analysis, and design artifacts for UKLabsMS. The global artifacts describe the wider business scope; the Sprint 2 stories refine selected administration capabilities.

## 1. Documentation Map

| Artifact | Purpose |
|:---|:---|
| [Global artifacts](global-artifacts/README.md) | Shared vocabulary, supplementary requirements, use cases, and conceptual Domain Model |
| [US10 - Register a Test Type](US10/US10.md) | Registers Test Type catalog data |
| [US11 - Register a Parameter](US11/US11.md) | Registers measurable Parameters and metric-dependent reference values |
| [US12 - Register an Employee](US12/US12.md) | Defines employee registration and the complete shared Employee model |
| [US13 - List Employees by Role](US13/US13.md) | Consults the employees registered through the shared Employee repository |

The four user-story documents use the same sections: Requirements Engineering, OO Analysis, Design, Construction, Tests, Integration and Demo, Open Issues, Conclusion, and References. Each has SSD, DM, SD, and CD PlantUML sources and SVG exports.

## 2. Scope and Requirement Origins

The [global use-case documentation](global-artifacts/use-case-diagram.md) uses team identifiers `UC01`-`UC12` for the Sprint 1 business capabilities. These are not aliases for the Sprint 2 story numbers. In particular, `UC12` is View Test Results and Report, whereas `US12` is Register an Employee.

The acceptance criteria classified as official in US10-US12 are retained from the supplied story documents. US13 does not contain a verified official acceptance-criteria list; its criteria remain team proposals. The assignment and forum records are referenced sources, but their complete original text is not included in this package. A design decision, existing implementation behavior, or proposed verification must not be presented as a new stakeholder requirement.

## 3. Shared Domain and Dependencies

| Stories | Shared concepts and required relationship | Dependency direction |
|:---|:---|:---|
| US10 and US11 | One `TestType` catalog and one `Parameter` catalog; `TestTypeParameter` links a Test Type to an existing Parameter. Numeric reference ranges follow the US11 rules. | Registering either catalog entry does not require the other. Establishing their association is a separate configuration responsibility, currently not implemented. |
| US12 and US13 | One `Employee` model, one assigned `Role` per Employee, and one `EmployeeRepository` instance for the session. | US12 supplies employees for a non-empty US13 result. US13 can still consult an empty repository. |
| US10-US13 | Administrator actor, English terminology, ConsoleApp, and cross-cutting authentication requirement | Shared application context; catalog registration is not a prerequisite for employee registration or consultation. |

The global Domain Model permits a Test Type to have no parameter associations while being configured. This is a modeling decision supporting independent registration. Before a Test Type is used in a Registered Test, its associations must identify the prescribed parameters; this is a derived domain constraint. Neither statement implies that the association workflow already exists in the prototype.

The general Employee and Role concepts cover administrative employee records. The named professional participants in the clinical workflow retain their responsibilities; the accepted role catalog and its exact mapping to those names still require confirmation.

## 4. Shared Employee Design Contract

This is the common target design used by the US12 and US13 diagrams and documents. It is not a description of an already completed implementation.

| Component | Contract |
|:---|:---|
| Employee | `ID : int`, name, phone number, e-mail address, one role, and optional Doctor Index Number. `getID()` exposes the numeric ID. The Doctor Index Number is mandatory for a Specialist Doctor. |
| EmployeeRepository | One in-memory employee collection for the session; `getNextID()`, `existsByID(ID)`, `existsByPhoneNumber(...)`, `existsByEmailAddress(...)`, `add(employee)`, `findByRole(role)`, and `count()`. |
| ID sequence | Starts at 1 for an initially empty repository and advances after successful insertion. Preserving the sequence after rejection is a team proposal recorded in US12. |
| RegisterEmployee | Receives the shared repository and returns `std::optional<int>` from `execute(...)`: the assigned ID on success or no value on rejection. |
| ListEmployeesByRole | Receives a constant reference to that same repository. `execute(role) const` returns `std::vector<Employee>` from `findByRole(role)` without changing stored records. |
| ConsoleApp | Keeps the repository alive for both operations, displays the registration ID, and displays matching employees and the size of the returned collection. |
| Role matching | Both operations use the same role representation. The existing query is exact and case-sensitive; any catalog or normalization must be coordinated across both stories. |

US13 displays ID, name, and role as a proposed output subset. The shared entity still retains the contact information and conditional Doctor Index Number required by US12.

## 5. Implementation Status

Validation performed on 2026-11-08 used g++ 13.1 and C++17. A syntax check of the employee repository and ConsoleApp failed because both sources call `Employee::getCode()`, which is not declared by Employee. A separate executable excluding the uncompilable employee sources and tests ran the available catalog and shared-utility tests: 58 of 60 passed. All 54 US10/US11 tests passed (23 US10 and 31 US11); 4 of 6 shared-utility tests passed. The two shared case-conversion tests failed with `locale::facet::_S_create_c_locale name not valid`. The 12 employee tests were excluded, and there are no implemented US12 tests. These are partial results, not a successful full-project build or integrated workflow verification.

The commands, scope, and detailed evidence are recorded in the [2026-11-08 validation report](validation/2026-11-08-review.md).

| Area | Present in the supplied source | Remaining integration or verification |
|:---|:---|:---|
| US10 | TestType, TestTypeContainer, App, registration controller and view, console option; 23 tests passed in the isolated catalog run | The full application build remains blocked by the employee API; TestTypeParameter configuration is not implemented. |
| US11 | Parameter, ParameterRepository, RegisterParameter, metric classification and reference-value input, console option; 31 tests passed in the isolated catalog run | The full application build remains blocked by the employee API; reconcile the outstanding identifier case-comparison rule with the recorded client context. |
| US12 | Registration requirements and target design | RegisterEmployee, the complete shared employee fields, numeric sequence, validation, console option, and US12 tests are not implemented. |
| US13 | Employee, EmployeeRepository, ListEmployeesByRole, console option, and employee test sources | Current repository and ConsoleApp syntax checks fail on `getCode()` while Employee exposes `getID()`; the repository uses `existsByCode()`. Align this API and the textual prototype ID with the shared numeric-ID design. |
| US12 to US13 | ConsoleApp creates one initially empty repository for the US13 service | Pass the same repository to the future registration service and demonstrate registration followed by listing. This workflow is not currently available. |
| Cross-cutting requirements | In-memory prototype and console interface; shared-utility tests passed 4 of 6 in the isolated run | Two case-conversion tests fail because the requested locale is unavailable. Authentication, persistent storage, and the wider clinical workflows are not demonstrated by these four stories. |

The revised diagrams express the aligned design. Differences that remain in code are recorded in Construction and Open Issues rather than represented as completed implementation work.

## 6. Integration Verification

The following checks are required after implementation and API alignment:

1. Build the current Core and ConsoleApp, then run the existing US10, US11, and employee tests. Run US12 tests once implemented. Historical pass counts must not substitute for this verification.
2. Register Test Types and Parameters independently, preserving each story's format, uniqueness, and metric rules. When the association operation is implemented, link existing entries through TestTypeParameter and verify their identities are preserved.
3. With an initially empty employee repository, consult a role through US13 and confirm a valid empty result.
4. Register employees through US12 with distinct contacts, including two sharing a role and another with a different role. Verify numeric IDs and then list the first role through US13, checking the same IDs, names, roles, and matching count.
5. Reject a duplicate-contact registration and a Specialist Doctor registration missing the Doctor Index Number. Verify unchanged employee records and, under the proposed sequence rule, an unchanged next ID.
6. Repeat consultations and compare the complete records and ID sequence before and after. Querying must not alter employee data or consume IDs.
7. Verify the agreed role-matching rule, empty-input feedback, no-results feedback, and continued availability of all four menu flows after US12 is added.

## 7. Artifact Maintenance

Each user-story folder contains its document, PlantUML sources under `puml/`, and matching SVG exports under `svg/`. Regenerate the SVG after a source change and verify that the exported diagram is readable and agrees with its Markdown description.

The project template directory referenced by the original skeleton is not included here. The existing US10-US13 documents provide the common structure for this package. Team task ownership remains in [TeamMembersAndTasks.md](../TeamMembersAndTasks.md); an unassigned or incomplete task must not be inferred to be completed from its presence in this index.
