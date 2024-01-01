#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdint>

namespace cream
{
    using std::string;

// 默认进度条长度
#define CREAM_PROGRESS_BAR_LENGTH 50

	class ProgressBar
	{
	public:
		ProgressBar()
			: m_current_progress(0L),
              m_message(),
			  m_output_stream(stdout),
              m_last_output_length(0L) {}

		~ProgressBar(){}

	private:
		// 当前的进度
		uint32_t m_current_progress;
        // 附加消息
        string m_message;
		// 输出流
		FILE* m_output_stream;
        // 上次输出长度
        uint32_t m_last_output_length;

    private:
        // 清空上次输出
        void clear_last_output()
        {
            string blank_line;
            blank_line.assign(m_last_output_length, ' ');
            // 回退光标
            fprintf(m_output_stream, "\r");
            fprintf(m_output_stream, "%s", blank_line.c_str());
            fprintf(m_output_stream, "\r");
            fflush(m_output_stream);
        }

	public:
		// 设置当前值
		void set_value(uint32_t current_progress)	
        {
            const static char __rotate_suffix__[5] = "-\\|/";
            const static char __progress_bar_base__[CREAM_PROGRESS_BAR_LENGTH + 1] = "==================================================";
            // 进度值未变化
            if(m_current_progress == current_progress)
            {
                return ;
            }
            clear_last_output();
            // 设置当前值
            m_current_progress = current_progress;
            // 初始化打印进度条
            // 需要打印的进度字符数
            uint32_t progress_characters_cnt = (uint32_t)(1.0 * m_current_progress / 100 * CREAM_PROGRESS_BAR_LENGTH);
            // 计算偏移数，不能超过最大值
            uint32_t out_format_offset =
                (progress_characters_cnt > CREAM_PROGRESS_BAR_LENGTH) ? 
                CREAM_PROGRESS_BAR_LENGTH : progress_characters_cnt;
            // 计算总打印长度
            uint32_t print_cnt = 0;
            print_cnt += fprintf(m_output_stream, "[%-50s][%2d%%][%c]",
                    __progress_bar_base__ + CREAM_PROGRESS_BAR_LENGTH - out_format_offset,
                    m_current_progress,
                    __rotate_suffix__[m_current_progress % 4]);
            // 有消息打印消息
            if (!m_message.empty())
            {
                print_cnt += fprintf(m_output_stream, ": \"%s\"", m_message.c_str());
            }
            m_last_output_length = print_cnt;
            return;
	    }

        // 设置显示的消息
        void set_message(string const & message)
        {
            m_message = message;
        }

        // 清空显示的消息
        void clear_message()
        {
            m_message.clear();
        }
		
		// 结束进度条
		void finish()
        {
            fprintf(m_output_stream, "\n");
            return;
        }
	};
}