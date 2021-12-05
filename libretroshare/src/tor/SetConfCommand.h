/* Ricochet - https://ricochet.im/
 * Copyright (C) 2014, John Brooks <john.brooks@dereferenced.net>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other materials provided with the
 *      distribution.
 *
 *    * Neither the names of the copyright owners nor the names of its
 *      contributors may be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <functional>
#include "TorControlCommand.h"

namespace Tor
{

class SetConfCommand : public TorControlCommand
{
    //Q_PROPERTY(QString errorMessage READ errorMessage CONSTANT)
    //Q_PROPERTY(bool successful READ isSuccessful CONSTANT)

public:
    SetConfCommand();

    void setResetMode(bool resetMode);

    ByteArray build(const std::string &key, const std::string &value);
    ByteArray build(const std::list<std::pair<std::string, std::string> > &data);

    std::string errorMessage() const { return m_errorMessage; }
    bool isSuccessful() const;

//signals:
    void set_ConfSucceeded_callback(const std::function<void(void)>& f) { mConfSucceeded=f; }
    void set_ConfFailed_callback   (const std::function<void(int code)>& f){ mConfFailed=f; }

protected:
    std::string m_errorMessage;
    bool m_resetMode;

    std::function<void(void)> mConfSucceeded;
    std::function<void(int code)> mConfFailed;

    virtual void onReply(int statusCode, const ByteArray &data);
    virtual void onFinished(int statusCode);
};

}
