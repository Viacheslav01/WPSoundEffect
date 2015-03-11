#define CODEBEHIND

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using Microsoft.Phone.Controls;

namespace MediaElementSoundEffect
{
	public partial class MainPage
		: PhoneApplicationPage
	{
		public MainPage()
		{
			InitializeComponent();
			
#if CODEBEHIND
			LayoutRoot.Children.Remove(viewMediaElement);
#endif

			CreateMediaElement();
		}

		private MediaElement _mediaElement;

		[Conditional("CODEBEHIND")]
		private void CreateMediaElement()
		{
			_mediaElement = new MediaElement
			{
				AutoPlay = true
			};

			LayoutRoot.Children.Add(_mediaElement);
		}

		private void PlaySoundClick(object sender, RoutedEventArgs e)
		{
#if CODEBEHIND
			_mediaElement.Source = new Uri("/Assets/sound.wav", UriKind.Relative);
#else
			viewMediaElement.Source = new Uri("/Assets/sound.wav", UriKind.Relative);
#endif
		}
	}
}