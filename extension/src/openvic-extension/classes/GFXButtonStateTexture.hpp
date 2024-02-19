#pragma once

#include <godot_cpp/classes/atlas_texture.hpp>
#include <godot_cpp/classes/image_texture.hpp>

#include <openvic-simulation/utility/Getters.hpp>

namespace OpenVic {
	class GFXButtonStateTexture : public godot::ImageTexture {
		GDCLASS(GFXButtonStateTexture, godot::ImageTexture)

	public:
		enum ButtonState {
			HOVER,
			PRESSED,
			DISABLED,
			BUTTON_STATE_COUNT
		};

	private:
		ButtonState PROPERTY(button_state);
		godot::Ref<godot::Image> state_image;

	protected:
		static void _bind_methods();

	public:
		GFXButtonStateTexture();

		/* Create a GFXButtonStateTexture using the specified godot::Image. Returns nullptr if generate_state_image fails. */
		static godot::Ref<GFXButtonStateTexture> make_gfx_button_state_texture(
			ButtonState button_state, godot::Ref<godot::Image> const& source_image, godot::Rect2i const& region
		);

		/* Set the ButtonState to be generated by this class (calling this does not trigger state image generation). */
		void set_button_state(ButtonState new_button_state);

		/* Generate a modified version of the given region of source_image
		 * and update the underlying godot::ImageTexture to use it. */
		godot::Error generate_state_image(godot::Ref<godot::Image> const& source_image, godot::Rect2i const& region);

		static godot::StringName const& button_state_to_theme_name(ButtonState button_state);
		godot::StringName const& get_button_state_theme() const;
	};

	class GFXButtonStateHavingTexture : public godot::AtlasTexture {
		GDCLASS(GFXButtonStateHavingTexture, godot::AtlasTexture)

		std::array<godot::Ref<GFXButtonStateTexture>, GFXButtonStateTexture::BUTTON_STATE_COUNT> button_state_textures;

	protected:
		static void _bind_methods();

		godot::Ref<godot::Image> button_image;

		void _update_button_states();
		void _clear_button_states();

		GFXButtonStateHavingTexture();

	public:
		godot::Ref<GFXButtonStateTexture> get_button_state_texture(GFXButtonStateTexture::ButtonState button_state);
	};
}

VARIANT_ENUM_CAST(OpenVic::GFXButtonStateTexture::ButtonState);
