#include <iostream>
#include <thread>

#include <spdlog/spdlog.h>

#include "HttpServer.hpp"
#include "Scheduler.hpp"
#include "Communication.hpp"

#include "InputManager.hpp"
#include "Logic.hpp"
#include "StateManager.hpp"
#include "AnalyticsManager.hpp"
#include "OutputManager.hpp"

/* ===================== Configuration ===================== */

constexpr const char *INPUT_FILE_PATH =
    "D:\\Mahmood_Reda\\SmartIoT-Assistant\\data\\input.json";

constexpr int INPUT_PERIOD_MS = 1000;
constexpr int LOGIC_PERIOD_MS = 1000;
constexpr int ANALYTICS_PERIOD_MS = 5000;
constexpr int SYSTEM_RUNTIME_MS = 10000;

/* ===================== Runtime Context ===================== */

struct RuntimeContext
{
    InputData rawData{};
    InputData validatedData{};
    bool isValid{false};
    SystemState decision{SystemState::SLEEP};
};

/* ===================== Main ===================== */

int main()
{
    /* ---------- Logging ---------- */
    spdlog::set_level(spdlog::level::info);
    spdlog::info("SmartIoT Assistant starting...");

    /* ---------- HTTP Server ---------- */
    HttpServer httpServer;
    httpServer.start();

    /* ---------- Core Objects ---------- */
    Scheduler scheduler;
    Communication communication(INPUT_FILE_PATH);

    InputManager inputManager;
    LogicManager logicManager;
    StateManager stateManager;
    AnalyticsManager analytics;
    OutputManager output;

    RuntimeContext ctx;

    /* =======================================================
       Task 1: Read & Validate Input
       ======================================================= */
    scheduler.addTask(Task(
        "ReadAndValidateInput",
        [&]()
        {
            spdlog::info("[TASK] Read & Validate Input");

            ctx.rawData = communication.readData();
            ctx.isValid = inputManager.validateInputData(
                ctx.rawData,
                ctx.validatedData);

            spdlog::info("[TASK] Validation result: {}",
                         ctx.isValid ? "VALID" : "INVALID");
        },
        INPUT_PERIOD_MS));

    /* =======================================================
       Task 2: Logic + State Update
       ======================================================= */
    scheduler.addTask(Task(
        "LogicAndState",
        [&]()
        {
            if (!ctx.isValid)
            {
                spdlog::warn("[TASK] Skipping logic (invalid data)");
                return;
            }

            ctx.decision = logicManager.decideState(ctx.validatedData);

            spdlog::info("[TASK] Decision: {}",
                         stateToString(ctx.decision));

            stateManager.updateState(ctx.decision);
            output.printState(ctx.decision);
        },
        LOGIC_PERIOD_MS));

    /* =======================================================
       Task 3: Analytics
       ======================================================= */
    scheduler.addTask(Task(
        "Analytics",
        [&]()
        {
            analytics.update(ctx.decision, ctx.validatedData);
            AnalyticsReport report = analytics.getReport();
            output.printAnalytics(report);
        },
        ANALYTICS_PERIOD_MS));

    /* ---------- Run System ---------- */
    spdlog::info("Scheduler running...");
    scheduler.run(SYSTEM_RUNTIME_MS);

    /* ---------- Shutdown ---------- */
    httpServer.stop();
    spdlog::info("SmartIoT Assistant stopped.");

    return 0;
}
