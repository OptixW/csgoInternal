#pragma once
#include <cstring>
#include <Windows.h>
#include <memory>

class CVMTHookManager
{
public:
    CVMTHookManager() = default;

    explicit CVMTHookManager(DWORD** ppdwClassBase)
    {
        initialize(ppdwClassBase);
    }

    ~CVMTHookManager()
    {
        unhook();
    }

    bool initialize(DWORD** ppdwClassBase)
    {
        m_ppdwClassBase = ppdwClassBase;
        m_pdwOldVMT = *ppdwClassBase;
        m_dwVMTSize = getVMTCount(*ppdwClassBase);
        m_pdwNewVMT = std::make_unique<DWORD[]>(m_dwVMTSize);
        std::memcpy(m_pdwNewVMT.get(), m_pdwOldVMT, sizeof(DWORD) * m_dwVMTSize);
        *ppdwClassBase = m_pdwNewVMT.get();
        return true;
    }

    void unhook()
    {
        if (m_ppdwClassBase)
        {
            *m_ppdwClassBase = m_pdwOldVMT;
        }
    }

    void rehook()
    {
        if (m_ppdwClassBase)
        {
            *m_ppdwClassBase = m_pdwNewVMT.get();
        }
    }

    int getFuncCount() const
    {
        return static_cast<int>(m_dwVMTSize);
    }

    DWORD getMethodAddress(int index) const
    {
        if (index >= 0 && index <= static_cast<int>(m_dwVMTSize) && m_pdwOldVMT)
        {
            return m_pdwOldVMT[index];
        }
        return nullptr;
    }

    DWORD* getOldVMT() const
    {
        return m_pdwOldVMT;
    }

    DWORD hookMethod(DWORD dwNewFunc, unsigned int index)
    {
        if (m_pdwNewVMT && m_pdwOldVMT && index <= m_dwVMTSize && index >= 0)
        {
            m_pdwNewVMT[index] = dwNewFunc;
            return m_pdwOldVMT[index];
        }

        return nullptr;
    }

private:
    DWORD getVMTCount(DWORD* pdwVMT) const
    {
        DWORD dwIndex = 0;

        while (pdwVMT[dwIndex])
        {
            if (IsBadCodePtr(reinterpret_cast<FARPROC>(pdwVMT[dwIndex])))
            {
                break;
            }
            dwIndex++;
        }
        return dwIndex;
    }

    DWORD** m_ppdwClassBase{ nullptr };
    std::unique_ptr<DWORD[]> m_pdwNewVMT;
    DWORD* m_pdwOldVMT{ nullptr };
    DWORD m_dwVMTSize{ 0 };
};
