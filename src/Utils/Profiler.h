#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

namespace Utils
{
    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        std::thread::id ThreadID;
    };

    struct InstrumentationSession
    {
        std::string Name;
    };

    class Instrumentor
    {
    private:
        std::mutex m_Mutex;
        InstrumentationSession* m_CurrentSession;
        std::ofstream m_OutputStream;
    public:
        Instrumentor() : m_CurrentSession(nullptr) {}

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            if (m_CurrentSession) {
                InternalEndSession();
            }
            m_OutputStream.open("src/Utils/Profiler_" + filepath);
            if (m_OutputStream.is_open()) {
                m_CurrentSession = new InstrumentationSession({ name });
                WriteHeader();
            }
        }

        void EndSession()
        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            InternalEndSession();
        }

        void WriteProfile(const ProfileResult& result)
        {
            std::stringstream json;

            json << ",{";
            json << "\"cat\":\"function\",";
            json << "\"dur\":" << (result.End - result.Start) << ',';
            json << "\"name\":\"" << result.Name << "\",";
            json << "\"ph\":\"X\",";
            json << "\"pid\":0,";
            json << "\"tid\":" << result.ThreadID << ",";
            json << "\"ts\":" << result.Start;
            json << "}";

            std::lock_guard<std::mutex> lock(m_Mutex);
            if (m_CurrentSession) {
                m_OutputStream << json.str();
                m_OutputStream.flush();
            }
        }

        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }

        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
            m_OutputStream.flush();
        }

        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }

        void InternalEndSession()
        {
            if (m_CurrentSession) {
                WriteFooter();
                m_OutputStream.close();
                delete m_CurrentSession;
                m_CurrentSession = nullptr;
            }
        }
    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name) : m_Name(name), m_Stopped(false)
        {
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

            uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
            Instrumentor::Get().WriteProfile({ m_Name, start, end, std::this_thread::get_id() });

            m_Stopped = true;
        }
    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
        bool m_Stopped;
    };
}

#define VK_PROFILE 1
#if VK_PROFILE
#define VK_PROFILE_BEGIN_SESSION(name, filepath) ::Utils::Instrumentor::Get().BeginSession(name, filepath)
#define VK_PROFILE_END_SESSION() ::Utils::Instrumentor::Get().EndSession()
#define VK_PROFILE_SCOPE(name) ::Utils::InstrumentationTimer timer##__LINE__(name);
#define VK_PROFILE_FUNCTION() VK_PROFILE_SCOPE(__FUNCSIG__)
#else
#define VK_PROFILE_BEGIN_SESSION(name, filepath)
#define VK_PROFILE_END_SESSION()
#define VK_PROFILE_SCOPE(name)
#define VK_PROFILE_FUNCTION()
#endif 