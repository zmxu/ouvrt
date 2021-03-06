/*
 * Oculus Rift DK2 HMD USB HID reports
 * Copyright 2015-2016 Philipp Zabel
 * SPDX-License-Identifier:	LGPL-2.0+ or BSL-1.0
 */
#ifndef __RIFT_DK2_HID_REPORTS__
#define __RIFT_DK2_HID_REPORTS__

#include <asm/byteorder.h>

#define RIFT_DK2_CONFIG_REPORT_ID		0x02

#define RIFT_DK2_CONFIG_USE_CALIBRATION		0x04
#define RIFT_DK2_CONFIG_AUTO_CALIBRATION	0x08
#define RIFT_DK2_CONFIG_SENSOR_COORDINATES	0x40

struct rift_dk2_config_report {
	__u8 id;
	__u16 echo;
	__u8 flags;
	__u8 packet_interval;
	__le16 sample_rate;
} __attribute__((packed));

#define RIFT_DK2_POSITION_REPORT_ID		0x0f

struct rift_dk2_position_report {
	__u8 id;
	__u16 echo;
	__u8 reserved_1;
	__le32 pos[3];
	__le16 dir[3];
	__le16 reserved_2;
	__le16 index;
	__le16 num;
	__le16 type;
} __attribute__((packed));

#define RIFT_DK2_LED_PATTERN_REPORT_ID		0x10

struct rift_dk2_led_pattern_report {
	__u8 id;
	__u16 echo;
	__u8 pattern_length;
	__le32 pattern;
	__le16 index;
	__le16 num;
} __attribute__((packed));

#define RIFT_DK2_KEEPALIVE_REPORT_ID		0x11

#define RIFT_DK2_KEEPALIVE_TYPE			0x0b
#define RIFT_DK2_KEEPALIVE_TIMEOUT_MS		10000

struct rift_dk2_keepalive_report {
	__u8 id;
	__le16 echo;
	__u8 type;
	__le16 timeout_ms;
} __attribute__((packed));

#define RIFT_DK2_TRACKING_REPORT_ID		0x0c

#define RIFT_DK2_TRACKING_ENABLE		0x01
#define RIFT_DK2_TRACKING_AUTO_INCREMENT	0x02
#define RIFT_DK2_TRACKING_USE_CARRIER		0x04
#define RIFT_DK2_TRACKING_SYNC_INPUT		0x08
#define RIFT_DK2_TRACKING_VSYNC_LOCK		0x10
#define RIFT_DK2_TRACKING_CUSTOM_PATTERN	0x20

#define RIFT_DK2_TRACKING_EXPOSURE_US		350
#define RIFT_DK2_TRACKING_PERIOD_US		16666
#define RIFT_DK2_TRACKING_VSYNC_OFFSET		0
#define RIFT_DK2_TRACKING_DUTY_CYCLE		0x7f

struct rift_dk2_tracking_report {
	__u8 id;
	__le16 echo;
	__u8 pattern;
	__u8 flags;
	__u8 reserved;
	__le16 exposure_us;
	__le16 period_us;
	__le16 vsync_offset;
	__u8 duty_cycle;
} __attribute__((packed));

#define RIFT_DK2_DISPLAY_REPORT_ID		0x0d

#define RIFT_DK2_DISPLAY_READ_PIXEL		0x04
#define RIFT_DK2_DISPLAY_DIRECT_PENTILE		0x08

struct rift_dk2_display_report {
	__u8 id;
	__u16 echo;
	__u8 brightness;
	__u8 flags1;
	__u8 flags2;
	__le16 unknown_6;
	__le16 persistence;
	__le16 lighting_offset;
	__le16 pixel_settle;
	__le16 total_rows;
} __attribute__((packed));

#define RIFT_DK2_SENSOR_MESSAGE_ID		0x0b

struct rift_dk2_imu_sample {
	__be64 accel;				/* packed, 10⁻⁴ m/s² */
	__be64 gyro;				/* packed, 10⁻⁴ rad/s */
} __attribute__((packed));

struct rift_dk2_sensor_message {
	__u8 id;
	__le16 echo;
	__u8 num_samples;
	__le16 sample_count;
	__le16 temperature;			/* 10⁻² °C */
	__le32 timestamp;			/* µs, wraps every ~72 min */
	struct rift_dk2_imu_sample sample[2];
	__le16 mag[3];
	__le16 frame_count;			/* HDMI input frame count */
	__le32 frame_timestamp;			/* HDMI vsync timestamp */
	__u8 frame_id;				/* frame id pixel readback */
	__u8 led_pattern_phase;
	__le16 exposure_count;
	__le16 exposure_timestamp;
	__le16 reserved;
} __attribute__((packed));

#endif /* __RIFT_DK2_HID_REPORTS__ */
