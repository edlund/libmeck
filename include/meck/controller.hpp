
/* meck - Mediocre (Entertainment Creation Kit)
 * Copyright(c) 2016, Erik Edlund <erik.edlund@32767.se>
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 *  * Neither the name of Erik Edlund, nor the names of its contributors may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * ----
 * 
 * Parts of meck are based on libSDL2pp - "C++11 bindings/wrapper for SDL2"
 * by Dmitry Marakasov <amdmi3@amdmi3.ru>. libSDL2pp can be found at:
 * 
 *     https://github.com/libSDL2pp/libSDL2pp
 * 
 * Code taken from libSDL2pp is most often altered and is not necessarily
 * representative of the original software.
 * 
 * libSDLpp is made available under the following conditions:
 * 
 * Copyright (C) 2013-2015 Dmitry Marakasov <amdmi3@amdmi3.ru>
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 * 
 *  2. Altered source versions must be plainly marked as such, and must not
 *     be misrepresented as being the original software.
 * 
 *  3. This notice may not be removed or altered from any source distribution.
 */

#ifndef MECK_CONTROLLER_HPP
#define MECK_CONTROLLER_HPP

#include <memory>
#include <queue>

#include <boost/noncopyable.hpp>

#include <meck/error.hpp>
#include <meck/keycode.hpp>
#include <meck/reactor.hpp>
#include <meck/typeid.hpp>

#include <meck/ui/overlay.hpp>

#include <SDL.h>

namespace meck {

class application;
class keycode_dispatcher;

/**
 * The controller is responsible for handling application
 * events. Each controller queued for use by an application
 * will be used for at least one rendered frame.
 */
class controller
	: private boost::noncopyable
	, public reactor
{
public:
	explicit
	controller(
		application& app
	);
	
	virtual
	~controller() noexcept;
	
	virtual void
	init() {
		ui_overlay_.init();
		name_ = demangle(typeid(*this).name());
	}
	
	virtual void
	finalize() {
		ui_overlay_.finalize();
	}
	
	virtual void
	prepare() {}
	
	virtual bool
	react(
		::SDL_Event& event
	);
	
	virtual const char*
	get_name() const noexcept {
		return name_.c_str();
	}
	
	virtual application&
	get_application() {
		return app_;
	}
	
	virtual keycode_dispatcher&
	get_keycode_dispatcher() {
		return keycode_dispatcher_;
	}
	
	virtual ui::overlay&
	get_ui_overlay() {
		return ui_overlay_;
	}
	
protected:
	std::string name_;
	application& app_;
	keycode_dispatcher keycode_dispatcher_;
	ui::overlay ui_overlay_;
};

typedef std::shared_ptr<controller> controller_ptr;
typedef std::queue<controller_ptr> controller_queue;

} // namespace:meck

#endif

